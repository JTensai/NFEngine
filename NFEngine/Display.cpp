#include "Display.h"
#include <GLEW\glew.h>
#include <iostream>
#include <glm\gtx\rotate_vector.hpp>
#include "InputManager.h"


Display::Display(int width, int height, const std::string& title)
{
	//std::cout << "Initializing Window" << std::endl;
	// Initialize Window
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // will get "At least" 8 bits
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window); // modifies the operating systems control of the window to allow the GPU to draw directly to the window
	//std::cout << "Finished Initializing Window" << std::endl;
	// Done Initializing Window


	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::cerr << "GLEW failed to initialize!" << std::endl;
	}

	m_is_closed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	clear(0.0f, 0.15f, 0.3f, 1.0f);
	update();
	//std::cout << "Finished Initializing Display" << std::endl;
}


Display::~Display()
{

	//std::cout << "Destroying Display" << std::endl;
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

	//std::cout << "Finished Destroying Display" << std::endl;
}

bool Display::isClosed()
{
	return m_is_closed;
}

void Display::clear(float r, float g, float b, float a) {

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update() {

	//std::cout << "Updating Display" << std::endl;
	if (InputManager::getInputManager().esc_pressed)
		m_is_closed = true;

	SDL_GL_SwapWindow(m_window);
}