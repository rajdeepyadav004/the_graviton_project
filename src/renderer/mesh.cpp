


#include "mesh.hpp"



mesh::mesh(){
    
}

mesh::mesh(vector<vec4>* arg_vertices, vector<vec4>* arg_colors, int arg_triangle_strips, GLenum arg_mode){

    this->m_vertices = arg_vertices;
    this->m_colors = arg_colors;
    this->triangle_strips = arg_triangle_strips;
    this->mode = arg_mode;

};  
