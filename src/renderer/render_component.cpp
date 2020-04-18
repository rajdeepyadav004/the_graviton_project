#include "render_component.hpp"


using namespace std;
using namespace glm;


extern GLuint programID;


render_component::render_component(const mesh & arg_mesh){

    this->m_mesh = arg_mesh;
    this->m_translation = mat4(1.0f);
    this->m_rotation = mat4(1.0f);
    this->m_scale = mat4(1.0f);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, m_mesh.m_vertices->size()*sizeof((*m_mesh.m_vertices)[0]), &(*m_mesh.m_vertices)[0], GL_DYNAMIC_DRAW);


    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, m_mesh.m_colors->size()*sizeof((*m_mesh.m_colors)[0]), &(*m_mesh.m_colors)[0], GL_DYNAMIC_DRAW);

    transformID = glGetUniformLocation(programID, "transform");

}


void render_component::translate(const vec3 & displacement){
    this->m_translation = glm::translate(this->m_translation, displacement);
}

void render_component::rotate(const GLfloat & angle, const vec3 & axis){
    this->m_rotation = glm::rotate(this->m_rotation, angle, axis);
}

void render_component::scale(const vec3 & scale_params){
    this->m_scale = glm::scale(this->m_scale, scale_params);
}

void render_component::set_position(const vec3 & position){
    m_translation = glm::translate(mat4(1.f), position);
}

void render_component::render(GLuint programID){


    glUseProgram(programID);

    mat4 transform = m_translation * m_rotation * m_scale;

    glUniformMatrix4fv(transformID, 1, GL_FALSE, &transform[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_mesh.triangle_strips);
    
    glDisableVertexAttribArray(0);    
    glDisableVertexAttribArray(1);


}