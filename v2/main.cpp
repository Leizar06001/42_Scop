// Include standard headers

#include "scop.hpp"
#include <random>
#include <ctime>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768


using namespace glm;

GLFWwindow* window;


float randomFloat() {
    static std::mt19937 gen(std::time(0)); // Seed the generator
    static std::uniform_real_distribution<> distr(0.0, 1.0); // Define the range
    
    return distr(gen);
}

int main( int argc, char **argv )
{
	// Initialize GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, "SCOP", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Disable VSync
	glfwSwapInterval(0);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set the mouse at the center of the screen
    glfwPollEvents();
	glfwSetCursorPos(window, WIN_WIDTH / 2, WIN_HEIGHT / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	// glEnable(GL_CULL_FACE);


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "shaders/vertexText.txt", "shaders/fragmentText.txt" );
	if (programID == 0) {
		return 1;
	}
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Create one OpenGl texture
	GLuint Texture = loadBMP_custom("image.bmp");
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");


	// Read our .obj file
	std::vector<glm::vec3> triVertices;
	std::vector<glm::vec2> triUvs;
	std::vector<glm::vec3> triNormals; 
	std::vector<glm::vec3> quadVertices;
	std::vector<glm::vec2> quadUvs;
	std::vector<glm::vec3> quadNormals; 
	bool res;
	if (argc > 1) {
		res = loadOBJ(argv[1], triVertices, triUvs, triNormals, quadVertices, quadUvs, quadNormals);
	} else {
		res = loadOBJ("teapot.obj", triVertices, triUvs, triNormals, quadVertices, quadUvs, quadNormals);
	}
	if (!res){
		std::cout << "Failed to load OBJ file, exit" << std::endl;
		return(1);
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	
	
	srand(static_cast<unsigned int>(time(0)));

	if(initText2D("resources/Holstein.DDS") == -1) {
		std::cout << "Failed to load font file, exit" << std::endl;
		return 1;
	}

	// For FPS
	double lastTime = glfwGetTime();
 	int nbFrames = 0, nbFrames2 = 0;
	float frameTime = 0;
	float fps_interval = 0.2;

	do {
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( (float)currentTime - (float)lastTime >= fps_interval ){ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			frameTime = (fps_interval * 1000)/double(nbFrames);
			nbFrames2 = nbFrames * (1.0 / fps_interval);
			// std::cout << frameTime << " ms/frame - " << nbFrames << " fps" << std::endl;
			nbFrames = 0;
			lastTime += fps_interval;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		computeMatricesFromInputs(WIN_WIDTH, WIN_HEIGHT);
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;


		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		// attribute, size, type, normalized, stride, array buffer offset
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		// std::cout << "triV : " << triVertices.size() << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, triVertices.size() * sizeof(glm::vec3), &triVertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, triUvs.size() * sizeof(glm::vec2), &triUvs[0], GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, triVertices.size()); // 3 indices starting at 0 -> 1 triangle

		// std::cout << "quadV : " << quadVertices.size() << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(glm::vec3), &quadVertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, quadUvs.size() * sizeof(glm::vec2), &quadUvs[0], GL_STATIC_DRAW);
		// Use GL_TRIANGLE_FAN instead of GL_QUADS
		for (size_t i = 0; i < quadVertices.size(); i += 4) {
			glDrawArrays(GL_TRIANGLE_FAN, i, 4);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		char text[256];
		sprintf(text,"%.2f ms / %d FPS", frameTime, nbFrames2);
		printText2D(text, 10, 580, 15);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Delete the text's VBO, the shader and the texture
	cleanupText2D();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
