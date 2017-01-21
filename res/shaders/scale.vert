#version 130

uniform float min_scale_y;
uniform float max_scale_y;

out float scale_point;

void main()
{
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    float miny = (min_scale_y/1080.)*2 - 1;
    float maxy = (max_scale_y/1080.)*2 - 1;
    scale_point = (gl_Position.y - miny)/(maxy - miny);

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}