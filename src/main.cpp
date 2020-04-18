#include <iostream>
#include <armadillo>

#include "renderer/models.hpp"
#include "world.hpp"

extern GLFWwindow* window;

using namespace std;


int main(){
    init_gl();
    


    world main_world;
    main_world.insert(rigidbody(1000,{0,0,0},{0,0,0}), render_component(get_cube()));
    main_world.insert(rigidbody(1,{5,0,0},{0,sqrt(G * 1000 / 5),0}), render_component(get_cube()));

    // veKush_back(rigidbody(1000,{0,0,0},{0,0,0}));


    do{        
        main_world.simulate(10000);
        main_world.render();
    }
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
    close_gl();
    return 0;
}

