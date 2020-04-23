#version 330 core

vec4 temp;

in vec4 frag_color;
in vec2 uvs;

out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
    
    color = vec4(texture(myTextureSampler, uvs).rgb, 1);

    // if(uvs[0] > 0.4 && uvs[0] < 0.6){
    //     color = vec4(1,0,0,1);
    // }
    // else{
    //     color = vec4(0,1,0,1);
    // }

    // color = frag_color;  

}