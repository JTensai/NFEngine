#pragma once
#include "GameObject.h"
#include <iostream>
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
class Crayon :
	public GameObject
{
public:
	Crayon(bool should_move = true);
	void Crayon::update(float delta_seconds);
	virtual ~Crayon();
private:
	bool should_move = false;
};

