#version 330 core

layout (location = 0) in vec4 v_position;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec2 in_uvs;
out vec4 frag_color;
out vec2 uvs;

uniform mat4 MVP;
uniform mat4 transform;

void main(){
    gl_Position = MVP * transform * v_position;
    frag_color = v_color;
    uvs = in_uvs;

    // if( out_uvs[0] >= 0 && out_uvs[0] <= 1 && out_uvs[1] >= 0 && out_uvs[1] <= 0.5){
    //     frag_color = vec4(0,1,0,1);
    // }
    // else{
    //     frag_color = vec4(1,0,0,1);
    // }
}