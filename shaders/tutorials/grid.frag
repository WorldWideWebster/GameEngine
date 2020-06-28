#version 330 core

out vec4 FragColor;

#define PI 3.141592

// size of a square in pixel
#define N 20.0

void main()
{
    vec2 Coord = gl_FragCoord.xy;

    // the grid in itself
    Coord = cos(PI/N*Coord);
    FragColor = vec4(1.0)-0.5*smoothstep(0.9,1.0,max(Coord.x,Coord.y));
}