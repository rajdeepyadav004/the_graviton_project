#include <iostream>
#define ARMA_ALLOW_FAKE_GCC
#include <armadillo>
#include "renderer/models.hpp"
#include "world.hpp"
#include "renderer/gl_util.hpp"

extern GLFWwindow* window;

using namespace std;


int main(){
    init_gl();
    
    int frames=0;
    world main_world(window, "scenes/scene1.xml");

    do {        
        main_world.simulate(10);
        main_world.render();
        frames++;
    }
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
    close_gl();
    std::cout<<frames<<endl;
    return 0;
}

