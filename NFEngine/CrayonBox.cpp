#include "CrayonBox.h"
#include "AssetManager.h"



CrayonBox::CrayonBox()
{
	this->transform = Transform();
	this->transform.translate(glm::vec3(-10, 0, 0));
	this->mesh = AssetManager::getAssetManager().getMesh("./res/CrayonBox2.obj");
	this->texture = AssetManager::getAssetManager().getTexture("./res/CrayonBox2.png");
}

void CrayonBox::update(float delta_seconds) {
	//std::cout << "I'm a crayon box!" << std::endl;
	//this->transform.setPosition(this->transform.getPosition() + glm::vec3(-delta_seconds, 0, 0));
	//this->transform.setRotation(this->transform.getRotation() + glm::vec3(0, -delta_seconds, 0));
}

CrayonBox::~CrayonBox()
{
}
