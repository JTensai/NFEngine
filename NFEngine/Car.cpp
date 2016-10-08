#include "Car.h"
#include "AssetManager.h"
#include <iostream>
#include "InputManager.h"


Car::Car()
{
	this->transform = Transform();
	this->transform.translate(glm::vec3(-2.5, 0, -7.5));
	//this->transform.rotate(-60, glm::vec3(0, 1, 0));
	this->transform.rotateDegrees(-60.f, glm::vec3(0, 1, 0));
	this->mesh = AssetManager::getAssetManager().getMesh("./res/car.obj");
	this->texture = AssetManager::getAssetManager().getTexture("./res/car.bmp");

	front_left = new Wheel(180);
	front_left->setParent(this);
	front_left->getTransform()->translate(glm::vec3(-0.375, .15, -0.5425));
	front_left->getTransform()->scale(glm::vec3(0.25, 0.25, 0.25));

	front_right = new Wheel(0);
	front_right->setParent(this);
	front_right->getTransform()->translate(glm::vec3(0.375, .15, -0.5425));
	front_right->getTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	//Transform test2(glm::vec3(0.375, .15, -0.5425), glm::vec3(0, glm::radians(240.f), 0), glm::vec3(0.25, 0.25, 0.25));
	//front_right->setTransform(test2);

	back_left = new Wheel(180);
	back_left->setParent(this);
	back_left->getTransform()->translate(glm::vec3(-0.375, .15, 0.48));
	back_left->getTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	//Transform test3(glm::vec3(-0.375, .15, 0.48), glm::vec3(0, glm::radians(60.f), 0), glm::vec3(0.25, 0.25, 0.25));
	//back_left->setTransform(test3);

	back_right = new Wheel(0);
	back_right->setParent(this);
	back_right->getTransform()->translate(glm::vec3(0.375, .15, 0.48));
	back_right->getTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	//Transform test4(glm::vec3(0.375, .15, 0.48), glm::vec3(0, glm::radians(240.f), 0), glm::vec3(0.25, 0.25, 0.25));
	//back_right->setTransform(test4);

	poro = GameObject();
	poro.setParent(this);
	poro.setMesh("./res/PoroGhostMerged.obj");
	poro.setTexture("./res/car.bmp");
	poro.getTransform()->translate(glm::vec3(0, .45, .07));
	poro.getTransform()->scale(glm::vec3(.04, .04, .04));
	poro.getTransform()->rotateDegrees(180.f, glm::vec3(0, 1, 0));

	//this->transform.setTranslation(glm::vec3(3, 3, 3));
}

void Car::update(float delta_seconds) {
	// modify wheel_angle based on current input
	if (InputManager::getInputManager().q_pressed && !InputManager::getInputManager().e_pressed) {
		turnLeft();
	}
	else if (InputManager::getInputManager().e_pressed && !InputManager::getInputManager().q_pressed) {
		turnRight();
	}
	else {
		straightenWheels();
	}

	// adjust wheel rotations if it has changed
	if (wheel_angle != wheel_angle_last_frame) {
		front_left->setWheelAngle(wheel_angle);
		front_right->setWheelAngle(wheel_angle);
	}
	wheel_angle_last_frame = wheel_angle;

	this->transform.rotateDegrees(1.f, glm::vec3(0, 1, 0));

}

void Car::turnLeft() {
	if (wheels_snap_to_rotation) {
		wheel_angle = -45.f;
	}
	else {
		if (wheel_angle > -45.f)
			wheel_angle -= 5;
	}
}

void Car::turnRight() {
	if (wheels_snap_to_rotation) {
		wheel_angle = 45.f;
	}
	else {
		if (wheel_angle < 45.f)
			wheel_angle += 5;
	}
}

void Car::straightenWheels() {
	if (wheels_snap_to_rotation) {
		wheel_angle = 0;
	}
	else {
		if (wheel_angle > 0)
			wheel_angle -= 5;
		if (wheel_angle < 0)
			wheel_angle += 5;
	}
}

Car::~Car()
{
}
