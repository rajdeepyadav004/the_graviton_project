#include <iostream>


#include "render_component.hpp"
#include "camera.hpp"
#include "models.hpp"
#include "mesh.hpp"
#include "gl_util.hpp"


extern GLFWwindow* window;

int main(){
    init_gl();
    

    vector<render_component> objects;
    camera main_camera;
    main_camera.set_projection_param(glm::radians(45.0f), (float)3/(float)2  , 0.1f, 100.0f);
	main_camera.set_view_param(glm::vec3(0,0,10), glm::vec3(0,0,0), glm::vec3(0,1,0));

    // objects.push_back(render_component(get_cube()));
    
    generate_icosahedron(); 
    mesh sphere = get_sphere(10);
    mesh cube = get_cube();
    mesh mesh2 = get_icosphere(5);
    mesh mesh1;
    mesh1.readObj("models/ico5.obj");

    mesh1.set_texture("images/2k_sun.bmp");
    mesh2.set_texture("images/2k_sun.bmp");



    objects.push_back(render_component(mesh2));
    objects[0].scale(vec3(3,3,3));

    do{
        main_camera.control(window);
        objects[0].rotate(glm::radians(0.05f), vec3(0,1,0));
        render_gl(objects, main_camera);
    }
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
    close_gl();
    return 0;
}

