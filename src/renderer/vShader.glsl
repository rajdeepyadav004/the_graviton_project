#version 330 core

layout (location = 0) in vec4 v_position;
layout (location = 1) in vec4 v_color;
out vec4 frag_color;

uniform mat4 MVP;
uniform mat4 transform;

void main(){
    gl_Position = MVP * transform * v_position;
    frag_color = v_color;
}