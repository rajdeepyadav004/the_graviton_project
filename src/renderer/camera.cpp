#include "camera.hpp"


camera::camera(){}

camera::~camera(){}

camera::camera(const camera& camera1){

    this->m_fov = camera1.m_fov;
    this->m_aspect_ratio = camera1.m_aspect_ratio;
    this->m_near_clip = camera1.m_near_clip;
    this->m_far_clip = camera1.m_far_clip;
    this->m_position = camera1.m_position;
    this->m_look_at = camera1.m_look_at;
    this->m_up_vector = camera1.m_up_vector;

}

camera::camera(GLfloat arg_fov, GLfloat arg_aspect_ratio, GLfloat arg_near_clip, GLfloat arg_far_clip){

    this->m_fov = arg_fov;
    this->m_aspect_ratio = arg_aspect_ratio;
    this->m_near_clip = arg_near_clip;
    this->m_far_clip = arg_far_clip;

}

void camera::set_projection_param(GLfloat arg_fov, GLfloat arg_aspect_ratio, GLfloat arg_near_clip, GLfloat arg_far_clip){
    this->m_fov = arg_fov;
    this->m_aspect_ratio = arg_aspect_ratio;
    this->m_near_clip = arg_near_clip;
    this->m_far_clip = arg_far_clip;
}

void camera::set_view_param(glm::vec3 arg_position, glm::vec3 arg_look_at, glm::vec3 arg_up_vector){

    this->m_position = vec4(arg_position,1);
    this->m_look_at = vec4(arg_look_at,1);
    this->m_up_vector = arg_up_vector;

}

void camera::translate(glm::vec3 displacement){
    this->m_position = glm::translate(mat4(1.f), displacement) * this->m_position;
    this->m_look_at = glm::translate(mat4(1.f), displacement) * this->m_look_at;
}

mat4 camera::get_camera_matrix(){

    mat4 projection_matrix = glm::perspective(m_fov, m_aspect_ratio, m_near_clip, m_far_clip);
    mat4 view_matrix = glm::lookAt(vec3(m_position), vec3(m_look_at), m_up_vector);
    return projection_matrix * view_matrix;

}

void camera::control(GLFWwindow* window){

    if(glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS){
        this->translate(vec3(0,0,-0.02));
    }

    if(glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS){
        this->translate(vec3(0,0,0.02));
    }

    if(glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS){
        this->translate(vec3(-0.02,0,0));
    }

    if(glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS){
        this->translate(vec3(0.02,0,0));
    }

    if(glfwGetKey (window, GLFW_KEY_DOWN) == GLFW_PRESS){
        this->translate(vec3(0,-0.02,0));
    }

    if(glfwGetKey (window, GLFW_KEY_UP) == GLFW_PRESS){
        this->translate(vec3(0,0.02,0));
    }


}