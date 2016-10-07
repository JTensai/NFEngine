#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Camera.h"

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void clear(float r, float g, float b, float a);
	void update();
	bool isClosed();
	void setCamera(Camera* camera) { m_camera = camera; }

	virtual ~Display();
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_is_closed;
	Camera* m_camera;

};

