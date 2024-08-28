#include "config.h"
#include "controller/app.h"

#include "components/camera_component.h"

#include "factories/factory.h"

int main() {

	App* app = new App();
	Factory* factory = new Factory(
		app->physicsComponents, app->renderComponents, 
		app->transformComponents, app->animationComponents,
		app->cameraComponents);
	
	factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f,0.0f});
	
	factory->make_cube(
		{3.0f, 0.0f, 0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 10.0f});

	factory->destroy_camera(0);

	factory->make_revy({4.0f, 2.0f, 0.25f}, {0.0f, 0.0f, 270.0f});

	factory->make_camera(
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f,0.0f});

	app->set_up_opengl();
	app->make_systems();

	app->run();

	delete app;
	return 0;
}