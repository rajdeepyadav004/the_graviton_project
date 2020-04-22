#ifndef MESH
#define MESH

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;



class mesh{
public:
    vector<vec4>* m_vertices;
    vector<vec4>* m_colors;

    vector<vec2>* m_uvs;

    int triangle_strips;
    GLenum mode;

    string texture_file;
    int texture_width, texture_height;

    mesh();
    mesh(vector<vec4>* arg_vertices, vector<vec4>* arg_colors, vector<vec2>* arg_uvs,int arg_triangle_strips, GLenum arg_mode);
    void set_texture(const char* filename);
};

#endif