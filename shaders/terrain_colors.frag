#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    sampler2D emission;
    float emissionBrightness;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// Max light definitions
#define MAX_POINT_LIGHTS 5
#define MAX_SPOT_LIGHTS 5
#define MAX_DIR_LIGHTS 1

uniform int u_num_point_lights = 0;
uniform int u_num_spot_lights = 0;
uniform int u_num_dir_lights = 0;

in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;

bool blinn = true;

// Function Prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// Check if lights are within the defined max, if not, set them to the max
void CheckLightNumbers(void);

int num_point_lights = 1;
int num_spot_lights = 1;
int num_dir_lights = 1;

void main()
{
    CheckLightNumbers();
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);

    // phase 1: Diretional Lighting
    for(int i = 0; i < u_num_dir_lights; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);

    // Phase 2: Point Lights
    for(int i = 0; i < u_num_point_lights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    // Phase 3: Spotlights
    for(int i = 0; i < u_num_point_lights; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    //emission
    vec3 emission = material.emissionBrightness * vertexColor;
    result += emission;

    FragColor = vec4(result, 1.0);
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    // combine results
    vec3 ambient = light.ambient * vec3(vertexColor);
    vec3 diffuse = light.diffuse * diff * vec3(vertexColor);
    vec3 specular = light.specular * spec * vec3(vertexColor);
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * vec3(vertexColor);
    vec3 diffuse = light.diffuse * diff * vec3(vertexColor);
    vec3 specular = light.specular * spec * vec3(vertexColor);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(vertexColor);
    vec3 diffuse = light.diffuse * diff * vec3(vertexColor);
    vec3 specular = light.specular * spec * vec3(vertexColor);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void CheckLightNumbers(void)
{
    num_dir_lights = (u_num_dir_lights > MAX_DIR_LIGHTS) ? MAX_DIR_LIGHTS : u_num_dir_lights;
    num_point_lights = (u_num_point_lights > MAX_POINT_LIGHTS) ? MAX_POINT_LIGHTS : u_num_point_lights;
    num_spot_lights = (u_num_spot_lights > MAX_SPOT_LIGHTS) ? MAX_SPOT_LIGHTS : u_num_spot_lights;
}
