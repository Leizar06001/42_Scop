#include "config.h"
#include "triangle_mesh.h"
#include "material.h"

/*  OPENGL installation

sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install libglew-dev
sudo apt-get install libglfw3-dev

*/

unsigned int make_module(const std::string& filepath, unsigned int module_type){
	std::ifstream 		file;
	std::stringstream 	bufferedLines;
	std::string 		line;

	file.open(filepath);
	if (!file.is_open()){
		std::cerr << "Failed to open " << filepath << std::endl;
		return -1;
	}
	while (std::getline(file, line)){
		bufferedLines << line << "\n";
	}
	std::string shaderSource = bufferedLines.str();
	const char *shaderSrc = shaderSource.c_str();
	bufferedLines.str("");
	file.close();

	unsigned int shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success){
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader module compilation error:\n" << errorLog << std::endl;
	}

	return shaderModule;
}

unsigned int make_shader(const std::string &vertex_filepath, const std::string &fragment_filepath){
	//To store all the shader modules
	std::vector<unsigned int> modules;

	//Add a vertex shader module
	modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
	//Add a fragment shader module
	modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

	//Attach all the modules then link the program
	unsigned int shader = glCreateProgram();
	for (unsigned int shaderModule : modules){
		glAttachShader(shader, shaderModule);
	}
	glLinkProgram(shader);

	//Check the linking worked
	int success;
	glGetShaderiv(shader, GL_LINK_STATUS, &success);
	if (!success){
		char errorLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, errorLog);
		std::cout << "Shader linking compilation error:\n" << errorLog << std::endl;
	}

	for (unsigned int shaderModule : modules){
		glDeleteShader(shaderModule);
	}

	return shader;
}


int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	std::ifstream file;
	std::string line;

	GLFWwindow* win;

	if (!glfwInit()){
		std::cout << "GLFW init error" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	// Open a window and create its OpenGL context
	win = glfwCreateWindow(800, 800, "SCOP", NULL, NULL);
	glfwMakeContextCurrent(win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
		return -1;
	}

	glClearColor(0.50f, 0.50f, 0.90f, 1.0f);
	//Set the rendering region to the actual screen size
	int w, h;
	glfwGetFramebufferSize(win, &w, &h);
	glViewport(0, 0, w, h);

	TriangleMesh* triangle = new TriangleMesh();
	Material* material = new Material((char*)"./resources/image.jpg");
	Material* mask = new Material((char*)"./resources/mask.png");

	unsigned int shader = make_shader(
		"./src/shaders/vertex.txt",
		"./src/shaders/fragment.txt"
	);

	//Set the texture units
	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "material"), 0);
	glUniform1i(glGetUniformLocation(shader, "mask"), 1);

	//configure alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

	while (!glfwWindowShouldClose(win) && 
			glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS){
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		material->use(0);
		mask->use(1);
		triangle->draw();

		glfwSwapBuffers(win);
	}

	glDeleteProgram(shader);
	delete triangle;
	delete material;
	delete mask;
	glfwTerminate();

	return (0);
}

