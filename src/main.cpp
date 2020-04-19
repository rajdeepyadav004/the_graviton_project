#include <iostream>
#define ARMA_ALLOW_FAKE_GCC
#include <armadillo>
#include "renderer/models.hpp"
#include "world.hpp"

extern GLFWwindow* window;

using namespace std;


int main(){
    init_gl();
    
    int frames=0;
    world main_world;
    main_world.insert(rigidbody(10000,{0,0,0},{0,0,0}), render_component(get_cube()));
    main_world.insert(rigidbody(1,{5,0,0},{0,sqrt( G * 10000 / 5),0}), render_component(get_cube()));

    do{        
        main_world.simulate(1);
        main_world.render();
        frames++;
    }
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
    close_gl();
    cout<<frames<<endl;
    return 0;
}

