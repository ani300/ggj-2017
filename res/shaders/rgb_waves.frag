#version 130

uniform vec2 source_pos1;
uniform vec2 source_pos2;
uniform vec2 source_pos3;
uniform vec2 source_pos4;
uniform float time;

uniform vec4 color1 = vec4(0.);
uniform float frequency1;
uniform float wavelength1 = 1.0;
uniform vec4 color2 = vec4(0.);
uniform float frequency2;
uniform float wavelength2 = 1.0;
uniform vec4 color3 = vec4(0.);
uniform float frequency3;
uniform float wavelength3 = 1.0;
uniform vec4 color4 = vec4(0.);
uniform float frequency4;
uniform float wavelength4 = 1.0;

vec4 sum_of_sources() {
    vec4 color(0.5,0.5,0.5,1.0);
    if (color1.a > 0.) {
        float dist1 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos1);
        float w1 = 2.0*3.141592*frequency1;
        float k1 = 2.0*3.141592/wavelength1;
        color.rgb += 0.5*sin(w1*time - k1*dist1)*color1.rgb; 
    }
    if (color2.a > 0.) {
        float dist2 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos2);
        float w2 = 2.0*3.141592*frequency2;
        float k2 = 2.0*3.141592/wavelength2;
        color.rgb += 0.5*sin(w2*time - k2*dist2)*color2.rgb;
    }
    if (color3.a > 0.) {
        float dist3 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos3);
        float w3 = 2.0*3.141592*frequency3;
        float k3 = 2.0*3.141592/wavelength3;
        color.rgb += 0.5*sin(w3*time - k3*dist3)*color3.rgb;
    }
    if (color4.a > 0.) {
        float dist4 = distance(vec2(gl_FragCoord.x, 1080.0 - gl_FragCoord.y), source_pos4);
        float w4 = 2.0*3.141592*frequency4;
        float k4 = 2.0*3.141592/wavelength4;
        color.rgb += 0.5*sin(w4*time - k4*dist4)*color4.rgb;   
    }
    return val/4.0;
}

void main() {
    vec4 sum = sum_of_sources();
    gl_FragColor = sum;
}