#ifndef MODELS
#define MODELS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.hpp"

mesh get_cube();
mesh get_sphere(int tesselation);
mesh get_icosphere(int recursion_depth);
void generate_icosahedron();

#endif