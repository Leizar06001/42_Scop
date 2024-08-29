#include <scop.hpp>

#include <random>
#include <ctime>

extern float posx;
extern float posy;
extern float posz;
extern float rotx;
extern float roty;
extern float rotz;
extern float fov;
extern float camx;
extern float camy;
extern float camz;

Vec3<float> camPos   = Vec3<float>(0.0f, 0.0f, 3.0f);
Vec3<float> camFront = Vec3<float>(0.0f, 0.0f, -1.0f);
Vec3<float> camUp    = Vec3<float>(0.0f, 1.0f, 0.0f);

float randomFloat() {
    static std::mt19937 gen(std::time(0)); // Seed the generator
    static std::uniform_real_distribution<> distr(-1.0, 1.0); // Define the range

    return distr(gen);
}

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

    float rot = 0.0f;
    float dec = 0.01f;

    	// For FPS
	double lastTime = glfwGetTime();
 	int nbFrames = 0, nbFrames2 = 0;
	float frameTime = 0;
	float fps_interval = 0.2;

    Vec3<float> objPos[] = {
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
        Vec3<float>(0.0f, 0.0f, 0.0f),
    };

    do {
        // Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( (float)currentTime - (float)lastTime >= fps_interval ){ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			frameTime = (fps_interval * 1000)/double(nbFrames);
			nbFrames2 = nbFrames * (1.0 / fps_interval);
			std::cout << frameTime << " ms/frame - " << nbFrames2 << " fps" << std::endl;
			nbFrames = 0;
			lastTime += fps_interval;
		}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        processInputs(env);

        float radius = 10.0f;
        camx = sin(glfwGetTime()) * radius;
        camz = cos(glfwGetTime()) * radius;

        Mat4 view = lookAt(camPos, camPos - camFront, camUp);
        // Mat4 view = lookAt(camPos, Vec3<float>(0.0f, 0.0f, 0.0f), camUp);
        Mat4 projection = Mat4::perspective(degToRad(fov), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

        for(int i = 0; i < 10; i++){
            Mat4 modelMatrix;

            rot += 0.001f;
            dec -= 0.0001f;
            // view = mat4translate(view, Vec3<float>(0.0f, 0.0f, -3.0f + posz));
            // view = mat4rotate(view, rotx, Vec3<float>(1.0f, 0.0f, 0.0f));
            // view = mat4rotate(view, roty, Vec3<float>(0.0f, 1.0f, 0.0f));

            modelMatrix = mat4scale(modelMatrix, Vec3<float>(2.5f, 2.5f, 2.5f));
            modelMatrix = mat4rotate(modelMatrix, rotx, Vec3<float>(1.0f, 0.0f, 0.0f));
            modelMatrix = mat4rotate(modelMatrix, roty, Vec3<float>(0.0f, 1.0f, 0.0f));
            modelMatrix = mat4rotate(modelMatrix, rotz, Vec3<float>(0.0f, 0.0f, 1.0f));

            if (i != 0){
                objPos[i].x += randomFloat() * 0.01;
                objPos[i].y += randomFloat() * 0.01;
                objPos[i].z += randomFloat() * 0.01;
                modelMatrix = mat4translate(modelMatrix, objPos[i]);
            }
            if (i == 0)
                modelMatrix = mat4translate(modelMatrix, Vec3<float>(posx, posy, 0.0f));

            unsigned int modelLoc = glGetUniformLocation(shader, "model");
            unsigned int viewLoc = glGetUniformLocation(shader, "view");
            unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix(0, 0));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view(0, 0));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection(0, 0));

            glUseProgram(shader);
            triangle->draw();
        }


        glfwSwapBuffers(env->window);

    } while( glfwWindowShouldClose(env->window) == 0 );
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
