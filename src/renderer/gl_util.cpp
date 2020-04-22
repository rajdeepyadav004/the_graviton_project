#include "gl_util.hpp"

using namespace std;
using namespace glm;

GLFWwindow * window;
GLuint programID, MatrixID, textureID;

void init_gl(){


	glewExperimental = GL_TRUE; 
	if( !glfwInit() ){
	cerr<<"Failed to initialize GLFW"<<endl;
	getchar();
	exit(1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 1080, 720, "Playground", NULL, NULL);
	if( window == NULL ){
		cerr<<"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials"<<endl;
		getchar();
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cerr<<"Failed to initialize GLEW:"<<endl;
		getchar();
		glfwTerminate();
		exit(1);
	}
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    programID = LoadShaders("src/renderer/vShader.glsl", "src/renderer/fShader.glsl");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	MatrixID = glGetUniformLocation(programID, "MVP");
	textureID = glGetUniformLocation(programID, "myTextureSampler");
}

void render_gl(vector<render_component> objects, camera main_camera){


	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);    


	mat4 mvp = main_camera.get_camera_matrix();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    for(auto it = objects.begin(); it!= objects.end(); ++it){
        it->render();
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void close_gl(){


    glfwTerminate();
    cout<<"closing"<<endl;
}