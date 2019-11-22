#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 vertexColor; // specify a color output to the fragment shader

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;


vec3 colorA = vec3(0.149,0.141,0.912);
vec3 colorB = vec3(1.000,0.833,0.224);


void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;


    TexCoords = aTexCoords;

    vertexColor = mix(colorA, colorB, FragPos.y/25.0);

    // TODO: separate colors

    gl_Position = projection * view * vec4(FragPos, 1.0);


}