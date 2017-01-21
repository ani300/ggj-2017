#version 130

uniform vec2 source_pos1;
uniform vec2 source_pos2;
uniform vec2 source_pos3;
uniform vec2 source_pos4;
uniform vec2 source_pos5;

uniform vec4 color_min;
uniform vec4 color_max;

uniform float time;

uniform float amplitude1 = 0.0;
uniform float frequency1;
uniform float wavelength1 = 1.0;
uniform float amplitude2 = 0.0;
uniform float frequency2;
uniform float wavelength2 = 1.0;
uniform float amplitude3 = 0.0;
uniform float frequency3;
uniform float wavelength3 = 1.0;
uniform float amplitude4 = 0.0;
uniform float frequency4;
uniform float wavelength4 = 1.0;
uniform float amplitude5 = 0.0;
uniform float frequency5;
uniform float wavelength5 = 1.0;

float sum_of_sources() {
    float dist1 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos1);
    float w1 = 2.0*3.141592*frequency1;
    float k1 = 2.0*3.141592/wavelength1;
    float val1 = 0.5 + amplitude1*0.5*sin(w1*time - k1*dist1);
    float dist2 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos2);
    float w2 = 2.0*3.141592*frequency2;
    float k2 = 2.0*3.141592/wavelength2;
    float val2 = 0.5 + amplitude2*0.5*sin(w2*time - k2*dist2);
    float dist3 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos3);
    float w3 = 2.0*3.141592*frequency3;
    float k3 = 2.0*3.141592/wavelength3;
    float val3 = 0.5 + amplitude3*0.5*sin(w3*time - k3*dist3);
    float dist4 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos4);
    float w4 = 2.0*3.141592*frequency4;
    float k4 = 2.0*3.141592/wavelength4;
    float val4 = 0.5 + amplitude4*0.5*sin(w4*time - k4*dist4);
    float dist5 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos5);
    float w5 = 2.0*3.141592*frequency5;
    float k5 = 2.0*3.141592/wavelength5;
    float val5 = 0.5 + amplitude5*0.5*sin(w5*time - k5*dist5);
    return (val1 + val2 + val3 + val4 + val5)/5.0;
}

void main() {
    gl_FragColor = mix(color_min, color_max, sum_of_sources());
}