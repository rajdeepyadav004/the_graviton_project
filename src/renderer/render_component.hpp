#ifndef OBJECT
#define OBJECT

#include <iostream>
#include "mesh.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.hpp"

using namespace std;
using namespace glm;

class camera;

class render_component{

    mesh m_mesh;
    mat4 m_translation, m_rotation, m_scale;
    GLuint VertexArrayID, vertexbuffer, colorbuffer, texturebuffer;
    GLuint transformID;
    GLuint texture;

public:

    render_component(const mesh & arg_mesh);
    void render();
    void translate(const vec3 & displacement);
    void rotate(const GLfloat & angle, const  vec3 & axis);
    void scale(const vec3 & scale_params);
    void set_position(const vec3 & position);
    friend camera;

};

#endif