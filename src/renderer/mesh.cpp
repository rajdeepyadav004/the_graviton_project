


#include "mesh.hpp"



mesh::mesh(){
    
}

mesh::mesh(vector<vec4>* arg_vertices, vector<vec4>* arg_colors, vector<vec2>* arg_uvs, int arg_triangle_strips, GLenum arg_mode){

    this->m_vertices = arg_vertices;
    this->m_colors = arg_colors;
    this->m_uvs = arg_uvs;
    this->triangle_strips = arg_triangle_strips;
    this->mode = arg_mode;
};  

void mesh::set_texture(const char* arg_file){

    this->texture_file = arg_file;
}