#version 130

uniform vec2 source_pos1;
uniform vec2 source_pos2;
uniform vec2 source_pos3;
uniform vec2 source_pos4;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

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

float sum_of_sources() {
    float val = 2.0;
    if (amplitude1 > 0.) {
        float dist1 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos1);
        float w1 = 2.0*3.141592*frequency1;
        float k1 = 2.0*3.141592/wavelength1;
        val += amplitude1*0.5*sin(w1*time - k1*dist1); 
    }
    if (amplitude2 > 0.) {
        float dist2 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos2);
        float w2 = 2.0*3.141592*frequency2;
        float k2 = 2.0*3.141592/wavelength2;
        val += amplitude2*0.5*sin(w2*time - k2*dist2);    
    }
    if (amplitude3 > 0.) {
        float dist3 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos3);
        float w3 = 2.0*3.141592*frequency3;
        float k3 = 2.0*3.141592/wavelength3;
        val += amplitude3*0.5*sin(w3*time - k3*dist3);    
    }
    if (amplitude4 > 0.) {
        float dist4 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos4);
        float w4 = 2.0*3.141592*frequency4;
        float k4 = 2.0*3.141592/wavelength4;
        val += amplitude4*0.5*sin(w4*time - k4*dist4);    
    }
    return val/4.0;
}

void main() {
    float sum = sum_of_sources();
    if (sum < 0.5)
        gl_FragColor = mix(color1, color2, sum*2);
    else
        gl_FragColor = mix(color2, color3, (sum - 0.5)*2);
}