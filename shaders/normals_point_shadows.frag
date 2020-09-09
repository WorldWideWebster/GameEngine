#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    mat3 TBN;
} fs_in;

struct DirLight {
    bool castsShadow;
    vec3 direction;
    vec3 color;
};

struct PointLight {
    bool castsShadow;
    vec3 position;

    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    bool castsShadow;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 color;

    float constant;
    float linear;
    float quadratic;
};


uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_height;
uniform samplerCube depthMap;

uniform vec3 viewPos;

uniform float far_plane;

// Max light definitions
#define MAX_POINT_LIGHTS 5
#define MAX_SPOT_LIGHTS 5
#define MAX_DIR_LIGHTS 1

uniform int u_num_point_lights = 0;
uniform int u_num_spot_lights = 0;
uniform int u_num_dir_lights = 0;

uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

// Function Prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 color, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 color, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 color, vec3 fragPos, vec3 viewDir);

int num_point_lights = 0;
int num_spot_lights = 0;
int num_dir_lights = 0;
uniform float heightScale;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos, vec3 lightPosition)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPosition;
    // use the fragment to light vector to sample from the depth map
    // float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    // closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    float bias = 1.0;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
        shadow += 1.0;
    }
    shadow /= float(samples);

    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);

    return shadow;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(texture_height, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(texture_height, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(texture_height, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

void main()
{
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 texCoords = fs_in.TexCoords;

    texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
//    if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
//    discard;

    // obtain normal from normal map in range [0,1]
    vec3 normal =  normalize(texture(texture_normal, fs_in.TexCoords).rgb * 2.0 - 1.0);
    vec3 color = texture(texture_diffuse, texCoords).rgb;

    vec3 result = vec3(0.0);

    // phase 1: Diretional Lighting
    for(int i = 0; i < u_num_dir_lights; i++)
        result += CalcDirLight(dirLights[i], normal, color, viewDir);
    // Phase 2: Point Lights
    for(int i = 0; i < u_num_point_lights; i++)
        result += CalcPointLight(pointLights[i], normal, color, fs_in.TangentFragPos, viewDir);
    // Phase 3: Spotlights
    for(int i = 0; i < u_num_spot_lights; i++)
        result += CalcSpotLight(spotLights[i], normal, color, fs_in.TangentFragPos, viewDir);
    FragColor = vec4(result, 1.0);
//    FragColor = vec4(fs_in.FragPos, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 color, vec3 viewDir)
{
    // ambient
    // diffuse
    vec3 lightDir = normalize(light.direction * fs_in.TBN);
    float diff = max(dot(lightDir, normal), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 ambient = 0.3 * color;
    vec3 diffuse = diff * light.color;
    vec3 specular = light.color * spec;
    float shadow = light.castsShadow ? ShadowCalculation(fs_in.FragPos, light.direction) : 0.0;


    return (ambient + (1.0 - shadow) * (diffuse + specular))*color;
}


// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 color, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position * fs_in.TBN - fs_in.TangentFragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    // attenuation
    float distance = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = 0.3 * color;
    vec3 diffuse = diff * light.color;
    vec3 specular = light.color * spec;

    float shadow = light.castsShadow ? ShadowCalculation(fs_in.FragPos, light.position) : 0.0;

    return ((ambient + (1.0 - shadow) * (diffuse + specular)) * color) * attenuation;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 color, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position * fs_in.TBN - fs_in.TangentFragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    // attenuation
    float distance = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction * fs_in.TBN));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = 1.0 * color;
    vec3 diffuse = diff * light.color;
    vec3 specular = light.color * spec;
    float shadow = light.castsShadow ? ShadowCalculation(fs_in.FragPos, light.position) : 0.0;

    return ((ambient + (1.0 - shadow) * (diffuse + specular)) * color) * attenuation * intensity;
}
