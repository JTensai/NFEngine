#include <iostream>
#include <ctime>
#include <GLEW\glew.h>
#include "Display.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Crayon.h"
#include "CrayonBox.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Car.h"

// move these to the display class with getters
#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv) 
{
	//std::cout << "Start Program" << std::endl;
	Display display(800, 600, "NF Engine");

	// hard coded shape to draw
	/*Vertex verts[] = {
		Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0, 0.0)),
	};*/

	//unsigned int indicies[] = { 0,1,2 };

	Shader shader("./res/basicShader");

	//Mesh mesh(verts, sizeof(verts) / sizeof(verts[0]), indicies, sizeof(indicies)/sizeof(indicies[0]));

	//GameObject poro(Transform(glm::vec3(0,0,0)));
	//Mesh poro_mesh("./res/PoroGhostMerged.obj");
	//Texture poro_texture("./res/PoroTemp.png");

	std::vector<GameObject*> game_objects;

	//game_objects.push_back(new Crayon());
	//game_objects.push_back(new Crayon(false));
	//game_objects.push_back(new CrayonBox());
	game_objects.push_back(new Car());
	game_objects.push_back(new GameObject("./res/ParkingLot.obj", "./res/ParkingLot.bmp"));
	game_objects.push_back(new GameObject("./res/Crayon.obj", "./res/violetCrayon.png"));
	//Wheel* test = new Wheel();
	//Crayon* parent_test = new Crayon();
	//test->setParent(parent_test);
	//game_objects.push_back(test);
	//game_objects.push_back(parent_test);

	Camera camera(glm::vec3(1.6,1,-9.0), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	display.setCamera(&camera);

	float counter = 0.0f;
	// end hard coding

	// example Enum setup and use
	//enum DrawType{
	//	CRAYON,
	//	CRAYON_BOX,
	//	PORO,
	//};
	//DrawType current_draw_type = PORO;

	//camera_transform.getRotation().y = 3.0f;

	clock_t last_frame = clock();
	clock_t time_elapsed = clock();
	float delta_seconds = 0.f;

	std::cout << "About to enter game loop" << std::endl;
	while (!display.isClosed()) {
		time_elapsed = clock() - last_frame;
		last_frame = clock();
		delta_seconds = time_elapsed / (CLOCKS_PER_SEC / 1000.f) / 1000.f;
		//std::cout << "FPS: " << 1.f / delta_seconds << std::endl;
		
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();

		for each (GameObject* obj in game_objects)
		{
			obj->primaryUpdate(delta_seconds);
			//shader.Update(obj->getCalculatedTransform(), camera);
			obj->draw(&shader, &camera);
		}
		camera.update(delta_seconds);
		//std::cout << "Meshes: " << AssetManager::getAssetManager().getNumMeshes() << std::endl;
		//std::cout << "Texture: " << AssetManager::getAssetManager().getNumTextures() << std::endl;

		display.update();
		InputManager::getInputManager().update();
	}

	return 0;
}