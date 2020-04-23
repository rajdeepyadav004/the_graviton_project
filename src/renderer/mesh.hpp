#ifndef MESH
#define MESH

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;


struct face{
    int v1, vt1, vn1;
    int v2, vt2, vn2;
    int v3, vt3, vn3;
};


class mesh{

public:
    vector<vec4> vertices;
    vector<vec2> texture_coordinates;
    vector<vec3> vertex_normals;
    vector<face> faces;

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
    void readObj(string filename);
    void saveObj(string filename);
};

#endif