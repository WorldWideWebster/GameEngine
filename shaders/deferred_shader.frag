#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpec;

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

#define MAX_POINT_LIGHTS 5
uniform int u_num_point_lights = 0;
int num_point_lights = 0;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Diffuse, float Specular);

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
//    for(int i = 0; i < nrOfLights; ++i)
//    {
//        // calculate distance between light source and current fragment
//        float distance = length(PointLight[i].Position - FragPos);
//        if(distance < PointLight[i].Radius)
//        {
//            // diffuse
//            vec3 lightDir = normalize(PointLight[i].Position - FragPos);
//            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * PointLight[i].Color;
//            // specular
//            vec3 halfwayDir = normalize(lightDir + viewDir);
//            float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
//            vec3 specular = PointLight[i].Color * spec * Specular;
//            // attenuation
//            float attenuation = 1.0 / (1.0 + PointLight[i].Linear * distance + PointLight[i].Quadratic * distance * distance);
//            diffuse *= attenuation;
//            specular *= attenuation;
//            lighting += diffuse + specular;
//        }
//    }
    vec3 result = vec3(0.0);

    // Phase 2: Point Lights
    for(int i = 0; i < u_num_point_lights; i++)
        lighting += CalcPointLight(pointLights[i], Normal, FragPos, viewDir, Diffuse, Specular);

//    FragColor = vec4(Normal.rgb, 1.0);
    FragColor = vec4(lighting, 1.0);

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
