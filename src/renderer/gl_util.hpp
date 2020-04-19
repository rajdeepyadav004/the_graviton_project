#ifndef UTIL
#define UTIL

#include <iostream>
#include <vector>
#include "render_component.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "camera.hpp"

using namespace std;
    
void init_gl();
void render_gl(vector<render_component> objects);
void close_gl();

#endif