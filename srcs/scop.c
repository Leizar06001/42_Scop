#include "scop.h"

#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>


/*  OPENGL installation 

sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install libglew-dev
sudo apt-get install libglfw3-dev


*/


void	glfw_loop(void)
{
	glfwPollEvents();
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int		main(int argc, char **argv)
{
	t_env	env;

	init(&env, argc, argv);
	load_obj(&env, env.model.filename);
	load_bmp(&env, "./resources/chaton.bmp");
	build_shader_program(&env);
	create_buffers(&env, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env.win.ptr))
	{
		glfw_loop();
		key_handle(&env);
		env.sim.model = mat4_mul(env.model.translation, env.model.rotation);
		glUseProgram(env.shader.program);
		compute_mvp_matrix(&env);
		update_shader_uniforms(&env);
		glBindTexture(GL_TEXTURE_2D, env.buffer.texture);
		glBindVertexArray(env.buffer.vao);
		glDrawElements(GL_TRIANGLES, env.model.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(env.win.ptr);
	}
	clean_glfw(&env);
	return (0);
}