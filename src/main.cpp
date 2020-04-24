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
    camera camera1(glm::radians(45.0f), (float)3/(float)2  , 0.1f, 100.0f);
    camera1.set_view_param(glm::vec3(0,0,10), glm::vec3(0,0,0), glm::vec3(0,1,0));
    world main_world(window, camera1);

    mesh mesh1;
    mesh1.readObj("models/ico5.obj");
    mesh1.set_texture("images/2k_sun.bmp");

    main_world.insert(rigidbody(10000,{0,0,0},{0,0,0}), render_component(mesh1));
    main_world.insert(rigidbody(1,{5,0,0},{0,sqrt( G * 10000 / 5),0}), render_component(mesh1));

    do {        
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

