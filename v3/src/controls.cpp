#include <scop.hpp>

float posx = 0.0f;
float posy = 0.0f;
float posz = 0.0f;
float rotx = 0.0f;
float roty = 0.0f;
float rotz = 0.0f;
float fov = 70.0f;

float camx = 0.0f;
float camy = 0.0f;
float camz = -6.0f;

extern Vec3<float> camPos;
extern Vec3<float> camFront;
extern Vec3<float> camUp;

float speed = 0.01f;
float rot_speed = 0.001f;

bool wireframe = false;
bool prev_wirePress = false;

void processInputs(t_env *env){
    if (glfwGetKey(env->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(env->window, true);
    }

    float cameraSpeed = 0.01f; // adjust accordingly
    if (glfwGetKey(env->window, GLFW_KEY_W) == GLFW_PRESS)
        camPos = camPos + (camFront * cameraSpeed);
    if (glfwGetKey(env->window, GLFW_KEY_S) == GLFW_PRESS)
        camPos = camPos - (camFront * cameraSpeed);
    if (glfwGetKey(env->window, GLFW_KEY_A) == GLFW_PRESS)
        camPos = camPos - vecNormalize(vecCrossProduct(camFront, camUp)) * cameraSpeed;
    if (glfwGetKey(env->window, GLFW_KEY_D) == GLFW_PRESS)
        camPos = camPos + vecNormalize(vecCrossProduct(camFront, camUp)) * cameraSpeed;

    // if (glfwGetKey(env->window, GLFW_KEY_W) == GLFW_PRESS){
    //     posy += speed;
    // }
    // if (glfwGetKey(env->window, GLFW_KEY_S) == GLFW_PRESS){
    //     posy -= speed;
    // }
    // if (glfwGetKey(env->window, GLFW_KEY_A) == GLFW_PRESS){
    //     posx -= speed;
    // }
    // if (glfwGetKey(env->window, GLFW_KEY_D) == GLFW_PRESS){
    //     posx += speed;
    // }
    if (glfwGetKey(env->window, GLFW_KEY_KP_ADD) == GLFW_PRESS){
        camPos.z += speed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS){
        camPos.z -= speed;
    }

    if (glfwGetKey(env->window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        roty += rot_speed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_LEFT) == GLFW_PRESS){
        roty -= rot_speed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_UP) == GLFW_PRESS){
        rotx -= rot_speed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_DOWN) == GLFW_PRESS){
        rotx += rot_speed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_Q) == GLFW_PRESS){
        rotz += rot_speed;
    }
    if (glfwGetKey(env->window, GLFW_KEY_E) == GLFW_PRESS){
        rotz -= rot_speed;
    }

    if (glfwGetKey(env->window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS){
        if (fov < 170.0f)
            fov += 0.1f;
    }
    if (glfwGetKey(env->window, GLFW_KEY_KP_DIVIDE) == GLFW_PRESS){
        if (fov > 10.0f)
            fov -= 0.1f;
    }

    // Wireframe
    if (glfwGetKey(env->window, GLFW_KEY_F) == GLFW_PRESS){
        if (!prev_wirePress){
            wireframe = !wireframe;
            if (wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            prev_wirePress = true;
        }
    } else {
        prev_wirePress = false;
    }


    if (glfwGetKey(env->window, GLFW_KEY_R) == GLFW_PRESS){
        posx = 0.0f;
        posy = 0.0f;
        posz = 0.0f;
        rotx = 0.0f;
        roty = 0.0f;
        rotz = 0.0f;
    }
}