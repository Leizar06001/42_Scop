#pragma once

#include <GL/glew.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "../external/glm-1.0.1/glm.hpp"

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_trivertices, 
	std::vector<glm::vec2> & out_triuvs,
	std::vector<glm::vec3> & out_trinormals,
    std::vector<glm::vec3> & out_quadvertices, 
	std::vector<glm::vec2> & out_quaduvs,
	std::vector<glm::vec3> & out_quadnormals
);