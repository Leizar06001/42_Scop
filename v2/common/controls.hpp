#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../external/glm-1.0.1/glm.hpp"
#include "../external/glm-1.0.1/gtc/matrix_transform.hpp"

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void computeMatricesFromInputs(int windowWidth, int windowHeight);