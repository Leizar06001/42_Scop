#ifndef SCOP_HPP
#define SCOP_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>

// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <triangle_mesh.h>

#define PROG_NAME "SCOP"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct s_env {
    GLFWwindow* window;
} t_env;


// init.cpp
int initOpenGl(t_env *env);
void cleanOpenGl(t_env *env);

// shaders.cpp
unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
unsigned int make_module(const std::string& filepath, unsigned int module_type);

// controls.cpp
void processInputs(t_env *env);

#endif