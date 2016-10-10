#pragma once
#include "GameObject.h"
class Wheel :
	public GameObject
{
public:
	Wheel(float initial_rotation);
	
	void setWheelAngle(float angle);
	void spinForwards(float speed);
	void spinBackwards(float speed);

	void Wheel::update(float);
	virtual ~Wheel();

	float initial_rotation = 0.f;
};

