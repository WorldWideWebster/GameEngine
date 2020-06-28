//Should work in most other versions
#version 330 core

uniform samplerCube dynamic_texture;

out vec4 FragColor;
in vec2 ST;

void main()
{
    float phi=ST.s*3.1415*2;
    float theta=(-ST.t+0.5)*3.1415;


    vec3 dir = vec3(cos(phi)*cos(theta),sin(theta),sin(phi)*cos(theta));

    //In this example i use a debthmap with only 1 channel, but the projection should work with a colored cubemap to
    float debth = texture( dynamic_texture, dir ).r;
    FragColor = vec4(vec3(debth),1);
}