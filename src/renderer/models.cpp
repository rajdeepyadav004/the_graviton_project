#include "models.hpp"

using namespace glm;





mesh get_cube(vec4 color){

    vector<vec4> vertices = {
        vec4(1.f, 1.f, 1.f,1.f),
        vec4(-1.f, 1.f, 1.f,1.f),
        vec4(1.f, 1.f, -1.f,1.f),
        vec4(-1.f, 1.f, -1.f,1.f),
        vec4(1.f, -1.f, 1.f,1.f),
        vec4(-1.f, -1.f, 1.f,1.f),
        vec4(-1.f, -1.f, -1.f,1.f),
        vec4(1.f, -1.f, -1.f,1.f),
    };

    vector<vec4> colors = {
        vec4(1.f, 1.f, 1.f,1.f),
        vec4(0.f, 1.f, 1.f,1.f),
        vec4(1.f, 1.f, 0.f,1.f),
        vec4(0.f, 1.f, 0.f,1.f),
        vec4(1.f, 0.f, 1.f,1.f),
        vec4(0.f, 0.f, 1.f,1.f),
        vec4(0.f, 0.f, 0.f,1.f),
        vec4(1.f, 0.f, 0.f,1.f),
    };

    vector<vec4> * cube_vertices = new vector<vec4>;
    vector<vec4>* cube_colors = new vector<vec4>;

    *cube_vertices = {
        vertices[3],
        vertices[2],
        vertices[6],
        vertices[7],
        vertices[4],
        vertices[2],
        vertices[0],
        vertices[3],
        vertices[1],
        vertices[6],
        vertices[5],
        vertices[4],
        vertices[1],
        vertices[0],
    };

    *cube_colors = {
        colors[3],
        colors[2],
        colors[6],
        colors[7],
        colors[4],
        colors[2],
        colors[0],
        colors[3],
        colors[1],
        colors[6],
        colors[5],
        colors[4],
        colors[1],
        colors[0],
    };

    return mesh(cube_vertices, cube_colors, 14);

}