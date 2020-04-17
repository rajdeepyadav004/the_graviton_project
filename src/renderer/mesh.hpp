#ifndef MESH
#define MESH

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;



class mesh{
public:
    vector<vec4>* m_vertices;
    vector<vec4>* m_colors;

    int triangle_strips;

    mesh();
    mesh( vector<vec4>* arg_vertices, vector<vec4>* arg_colors, int arg_triangle_strips);
};

#endif