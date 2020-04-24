#version 330 core

vec4 temp;

in vec4 frag_color;
in vec2 uvs;

out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
    
    color = vec4(texture(myTextureSampler, uvs).rgb, 1);
  
}