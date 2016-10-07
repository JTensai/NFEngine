#include "InputManager.h"

void InputManager::update(){
	// handles all the input received, and handles moving the camera here.
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
			//std::cout << "There was an error" << std::endl;
			//m_is_closed = true;
			esc_pressed = true;
		}
		switch (e.type) {
		case SDL_KEYDOWN:
			//printf("Key press detected: %s\n", SDL_GetKeyName(e.key.keysym.sym));
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				esc_pressed = true;
				break;
			case SDLK_w:
				w_pressed = true;
				break;
			case SDLK_s:
				s_pressed = true;
				break;
			case SDLK_q:
				q_pressed = true;
				break;
			case SDLK_e:
				e_pressed = true;
				break;
			case SDLK_a:
				a_pressed = true;
				break;
			case SDLK_d:
				d_pressed = true;
				break;
			case SDLK_r:
				r_pressed = true;
				break;
			case SDLK_f:
				f_pressed = true;
				break;
			case SDLK_LEFT:
				left_pressed = true;
				break;
			case SDLK_RIGHT:
				right_pressed = true;
				break;
			case SDLK_UP:
				up_pressed = true;
				break;
			case SDLK_DOWN:
				down_pressed = true;
				break;
			}
			break;

		case SDL_KEYUP:
			//printf("Key release detected: %s\n", SDL_GetKeyName(e.key.keysym.sym));
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				esc_pressed = false;
				break;
			case SDLK_w:
				w_pressed = false;
				break;
			case SDLK_s:
				s_pressed = false;
				break;
			case SDLK_q:
				q_pressed = false;
				break;
			case SDLK_e:
				e_pressed = false;
				break;
			case SDLK_a:
				a_pressed = false;
				break;
			case SDLK_d:
				d_pressed = false;
				break;
			case SDLK_r:
				r_pressed = false;
				break;
			case SDLK_f:
				f_pressed = false;
				break;
			case SDLK_LEFT:
				left_pressed = false;
				break;
			case SDLK_RIGHT:
				right_pressed = false;
				break;
			case SDLK_UP:
				up_pressed = false;
				break;
			case SDLK_DOWN:
				down_pressed = false;
				break;
			}
			break;

		default:
			break;
		}
	}
}