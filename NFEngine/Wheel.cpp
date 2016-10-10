#include "Wheel.h"
#include "AssetManager.h"
#include <iostream>
#include <glm\gtx\string_cast.hpp>

Wheel::Wheel(float initial_rotation)
{
	this->mesh = AssetManager::getAssetManager().getMesh("./res/tire.obj");
	this->texture = AssetManager::getAssetManager().getTexture("./res/tire.bmp");

	this->transform = Transform();
	this->initial_rotation = initial_rotation;
	this->transform.setRotation(glm::vec3(0,initial_rotation,0));
}


void Wheel::setWheelAngle(float angle) {
	transform.setRotation(glm::vec3(0, initial_rotation + angle, 0));
}

void Wheel::spinForwards(float speed)
{
	transform.rotate(speed * 1.75f, transform.getRight());
}

void Wheel::spinBackwards(float speed)
{
	transform.rotate(speed * -1.75f, -transform.getRight());
}

void Wheel::update(float delta_seconds) {
	//transform.rotate(1.f * delta_seconds, glm::vec3(1, 0, 0));
}

Wheel::~Wheel()
{
}
