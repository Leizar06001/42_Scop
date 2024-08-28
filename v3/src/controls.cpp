#include <scop.hpp>

void processInputs(t_env *env){
    if (glfwGetKey(env->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(env->window, true);
    }
}