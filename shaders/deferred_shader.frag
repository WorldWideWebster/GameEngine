#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpec;

struct Light {
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
    float Radius;
};
const int NR_LIGHTS = 32;
uniform Light PointLight[NR_LIGHTS];
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
    FragColor = vec4(Normal.rgb, 1.0);
}