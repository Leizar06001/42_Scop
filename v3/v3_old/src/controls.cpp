#include <scop.hpp>

static bool wireframe = false;
static bool prevKeyFrame = false;

float triDecx = 0.0f;
float triDecy = 0.0f;
float triDecz = 0.0f;

void processInputs(t_env *env){
    float decalSpeed = 0.01f;

    if (glfwGetKey(env->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(env->window, true);
    }
    if (glfwGetKey(env->window, GLFW_KEY_F) == GLFW_PRESS){
        if (!prevKeyFrame){
            prevKeyFrame = true;
            if (wireframe){
                wireframe = false;
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            } else {
                wireframe = true;
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
        }
    } else {
        prevKeyFrame = false;
    }
    if (glfwGetKey(env->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        decalSpeed = 0.05f;
    }
    if (glfwGetKey(env->window, GLFW_KEY_A) == GLFW_PRESS){
        if (triDecx > -1.0f)
            triDecx -= decalSpeed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_D) == GLFW_PRESS){
        if (triDecx < 1.0f)
            triDecx += decalSpeed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_W) == GLFW_PRESS){
        if (triDecy < 1.0f)
            triDecy += decalSpeed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_S) == GLFW_PRESS){
        if (triDecy > -1.0f)
            triDecy -= decalSpeed;
    }

}