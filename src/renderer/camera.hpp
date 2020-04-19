#ifndef CAMERA
#define CAMERA


#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;


class camera{

    GLfloat m_fov, m_aspect_ratio, m_near_clip, m_far_clip;
    vec4 m_position, m_look_at;
    vec3 m_up_vector;

public:

    camera();
    ~camera();
    
    camera(const camera& camera1);   
    camera(GLfloat arg_fov, GLfloat arg_aspect_ratio, GLfloat arg_near_clip, GLfloat arg_far_clip);
    
    void set_projection_param(GLfloat arg_fov, GLfloat arg_aspect_ratio, GLfloat arg_near_clip, GLfloat arg_far_clip);
    void set_view_param(vec3 arg_position, vec3 arg_look_at, vec3 arg_up_vector);

    void translate(vec3 displacement);
    mat4 get_camera_matrix();
};


#endif