#include <iostream>


#include "render_component.hpp"
#include "models.hpp"
#include "gl_util.hpp"


extern GLFWwindow* window;

int main(){
    init_gl();
    

    vector<render_component> objects;
    objects.push_back(render_component(get_cube()));
    
    objects.push_back(render_component(get_cube()));

    objects[0].translate(vec3(-1.5,0,0));
    objects[1].translate(vec3(1.5,0,0));

    do{
        objects[0].rotate(glm::radians(0.05f), vec3(0,1,0));
        objects[1].rotate(glm::radians(0.05f), vec3(0,-1,0));
        objects[0].set_position(vec3(-3,2,0));
        render_gl(objects);
    }
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
    close_gl();
    return 0;
}

