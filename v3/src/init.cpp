#include <scop.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int initOpenGl(t_env *env){
    if (!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // FOR OSX
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    env->window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, PROG_NAME, NULL, NULL);
    if (!env->window){
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(env->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(env->window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
    glfwPollEvents();
	glfwSetCursorPos(env->window, WIN_WIDTH / 2, WIN_HEIGHT / 2);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	// glEnable(GL_CULL_FACE);
    // Disable VSync
	glfwSwapInterval(0);
    // Callback for resizing window
    glfwSetFramebufferSizeCallback(env->window, framebuffer_size_callback);
    return 0;
}

void cleanOpenGl(t_env *env){

    glfwTerminate();
}