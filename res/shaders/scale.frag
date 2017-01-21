#version 130

varying float scale_point;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

void main()
{
    if (scale_point < 0.5) {
        gl_FragColor = mix(color1, color2, scale_point*2);    
    }
    else {
        gl_FragColor = mix(color2, color3, (scale_point - 0.5)*2); 
    }
}