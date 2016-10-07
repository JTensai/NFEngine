#include "Crayon.h"
#include "AssetManager.h"


Crayon::Crayon(bool should_move)
{
	this->transform = Transform();
	this->mesh = AssetManager::getAssetManager().getMesh("./res/Crayon.obj");
	this->texture = AssetManager::getAssetManager().getTexture("./res/violetCrayon.png");
	this->should_move = should_move;
}

void Crayon::update(float delta_seconds) {
	//std::cout << "I'm a crayon!" << std::endl;
	if (should_move) {
		//this->transform.setPosition(this->transform.getPosition() + glm::vec3(delta_seconds, 0, 0));
		//this->transform.setRotation(this->transform.getRotation() + glm::vec3(0, delta_seconds, 0));
	}
}

Crayon::~Crayon()
{
	//mesh->~Mesh();
	//texture->~Texture();
}
