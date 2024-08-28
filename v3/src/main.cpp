#include <scop.hpp>


int main_loop(t_env *env){
    TriangleMesh* triangle = new TriangleMesh();

    unsigned int shader = make_shader(
		"./shaders/vertSimple.txt", 
		"./shaders/fragSimple.txt"
	);
    if (shader == 0){
        delete triangle;
        return -1;
    }

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        glUseProgram(shader);
        triangle->draw();

        glfwSwapBuffers(env->window);

    } while( glfwGetKey(env->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(env->window) == 0 );
    delete triangle;
    glDeleteProgram(shader);
    return 0;
}

int main(){
    t_env env;

    (void)env;


    initOpenGl(&env);

    main_loop(&env);

    cleanOpenGl(&env);

    return 0;
}