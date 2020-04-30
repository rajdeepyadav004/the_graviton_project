#ifndef CAMERA
#define CAMERA

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "render_component.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;


class camera{

    GLfloat m_fov, m_aspect_ratio, m_near_clip, m_far_clip;
    glm::vec4 m_position, m_look_at;
    glm::vec3 m_up_vector;

public:

    camera();
    ~camera();
    
    camera(const camera& camera1);   
    camera(GLfloat arg_fov, GLfloat arg_aspect_ratio, GLfloat arg_near_clip, GLfloat arg_far_clip);
    
    void set_projection_param(GLfloat arg_fov, GLfloat arg_aspect_ratio, GLfloat arg_near_clip, GLfloat arg_far_clip);
    void set_view_param(glm::vec3 arg_position, glm::vec3 arg_look_at, glm::vec3 arg_up_vector);

    void translate(glm::vec3 displacement);
    void rotate(GLfloat angle,glm::vec3 axis);
    void rotate_up(double angle);
    
    mat4 get_camera_matrix();

    void control(GLFWwindow* window);
};

#endif