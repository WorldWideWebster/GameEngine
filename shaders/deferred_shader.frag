#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpec;


struct DirLight {
    bool castsShadow;
    vec3 direction;
    vec3 color;
};

struct PointLight
{
//    bool castsShadow;
    vec3 position;
    float radius;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
//    bool castsShadow;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 color;

    float constant;
    float linear;
    float quadratic;
};


#define MAX_DIR_LIGHTS 1
#define MAX_POINT_LIGHTS 5
#define MAX_SPOT_LIGHTS 5

uniform int u_num_dir_lights = 0;
uniform int u_num_point_lights = 0;
uniform int u_num_spot_lights = 0;

int num_point_lights = 0;
int num_dir_lights = 0;
int num_spot_lights = 0;

uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular);

uniform vec3 viewPos;
uniform int nrOfLights;
void main()
{
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;
    float Specular = texture(gSpec, TexCoords).a;

    // then calculate lighting as usual
    vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
    vec3 viewDir  = normalize(viewPos - FragPos);
    // phase 1: Diretional Lighting
    for(int i = 0; i < u_num_dir_lights; i++)
        lighting += CalcDirLight(dirLights[i], Normal, FragPos, viewDir, Diffuse, Specular);
    // Phase 2: Point Lights
    for(int i = 0; i < u_num_point_lights; i++)
        lighting += CalcPointLight(pointLights[i], Normal, FragPos, viewDir, Diffuse, Specular);
    // Phase 3: Spotlights
    for(int i = 0; i < u_num_spot_lights; i++)
        lighting += CalcSpotLight(spotLights[i], Normal, FragPos, viewDir, Diffuse, Specular);
//    FragColor = vec4(Normal.rgb, 1.0);
    FragColor = vec4(lighting, 1.0);

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular)
{
    vec3 lighting = vec3(0.0);
    // diffuse
    vec3 lightDir = normalize(light.direction);
    vec3 diffuse = max(dot(lightDir, normal), 0.0)  * Diffuse * light.color;
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = light.color * spec * Specular;

//    float shadow = light.castsShadow ? ShadowCalculation(fs_in.FragPos, light.direction) : 0.0;

    lighting += diffuse + specular;
    return lighting;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular)
{
    vec3 lighting = vec3(0.0);
    float distance = distance(light.position, fragPos);
    if(distance < light.radius)
    {
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        vec3 diffuse = max(dot(normal, lightDir), 0.0) * Diffuse * light.color;
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = light.color * spec * Specular;
        // attenuation
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // combine results
        ////    float shadow = light.castsShadow ? ShadowCalculation(fragPos, light.position) : 0.0;
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;
    }
    return lighting;
}


// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * Diffuse * light.color;
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = light.color * spec * Specular;
    // attenuation
    float distance = distance(light.position, fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    diffuse *= attenuation;
    specular *= attenuation;
//    float shadow = light.castsShadow ? ShadowCalculation(fs_in.FragPos, light.position) : 0.0;

    return (diffuse + specular) * intensity;
}
