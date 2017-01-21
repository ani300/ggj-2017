#version 130

in float scale_point;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

void main()
{
    float correct_scale = 1. - scale_point;
    if (correct_scale < 0.5) {
        gl_FragColor = mix(color1, color2, correct_scale*2);    
    }
    else {
        gl_FragColor = mix(color2, color3, (correct_scale - 0.5)*2); 
    }
}