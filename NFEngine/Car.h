#pragma once
#include "GameObject.h"
#include "Wheel.h"

class Car :
	public GameObject
{
public:
	Car();
	void update(float);
	void turnLeft();
	void turnRight();
	void straightenWheels();
	virtual ~Car();
private:
	Wheel* front_left;
	Wheel* front_right;
	Wheel* back_left;
	Wheel* back_right;
	GameObject& poro = GameObject();

	bool wheels_snap_to_rotation = false;
	float wheel_angle = 0.f;
	float wheel_angle_last_frame = wheel_angle;
};

