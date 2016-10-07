#pragma once
#include <SDL2/SDL.h>
class InputManager
{
public:
	static InputManager& getInputManager() {
		static InputManager instance;
		return instance;
	}

	void update();

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	bool esc_pressed = false;
	bool w_pressed = false;
	bool s_pressed = false;
	bool q_pressed = false;
	bool e_pressed = false;
	bool a_pressed = false;
	bool d_pressed = false;
	bool r_pressed = false;
	bool f_pressed = false;
	bool left_pressed = false;
	bool right_pressed = false;
	bool up_pressed = false;
	bool down_pressed = false;

private:
	InputManager() {};

	SDL_Event e;
};

