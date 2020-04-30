#version 330 core

vec4 temp;

vec2 tx;
in vec4 frag_color;
in vec2 uvs;
in vec3 pos;
out vec4 color;
uniform sampler2D myTextureSampler;

void main(){
    float u,v,x,y,pi=3.14159265359;
    x = pos.x;
    y = pos.y;
    u = 0.5 - atan(y,x)/2/pi;
    v = 0.5 - asin(pos.z)/pi;
    tx = vec2(u,v);    
    color = vec4(texture(myTextureSampler, tx).rgb, 1); 
}