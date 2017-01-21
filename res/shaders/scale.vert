#version 130

uniform float min_scale_y;
uniform float max_scale_y;
uniform vec2 globalCoords;
varying float scale_point;

void main()
{
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + vec4(globalCoords.x/1920., globalCoords.y/1080., 0, 1));
    gl_Position = vec4(1.0, 1.0, 0.0, 1.0);

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;

    scale_point = (gl_Vertex.y + globalCoords.y - min_scale_y)/(max_scale_y - min_scale_y);
}