#pragma once
#include "GameObject.h"
#include <iostream>
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"

class CrayonBox :
	public GameObject
{
public:
	CrayonBox();
	void CrayonBox::update(float delta_seconds);
	virtual ~CrayonBox();
};

