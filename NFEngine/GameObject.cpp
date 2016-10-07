#include "GameObject.h"
#include <iostream>
#include "AssetManager.h"


GameObject::GameObject()
{
	this->parent = nullptr;
	this->transform = Transform();
}

GameObject::GameObject(const std::string& mesh_file_name, const std::string& texture_file_name)
{
	this->parent = nullptr;
	this->transform = Transform();
	this->mesh = AssetManager::getAssetManager().getMesh(mesh_file_name);
	this->texture = AssetManager::getAssetManager().getTexture(texture_file_name);
}

void GameObject::setParent(GameObject* parent) {
	this->parent = parent;
	parent->addChild(this);
}

void GameObject::addChild(GameObject* child) {
	this->children.push_back(child);
}

void GameObject::setMesh(const std::string & file_name)
{
	this->mesh = AssetManager::getAssetManager().getMesh(file_name);
}

void GameObject::setTexture(const std::string & file_name)
{
	this->texture = AssetManager::getAssetManager().getTexture(file_name);
}

void GameObject::primaryUpdate(float delta_seconds)
{
	for each (GameObject* obj in children)
	{
		obj->primaryUpdate(delta_seconds);
	}
	this->update(delta_seconds);
	//std::cout << "Updating Game Object, no override given" << std::endl;
}

void GameObject::draw(Shader* shader, Camera* camera) {
	for each (GameObject* child in children)
	{
		child->draw(shader, camera);
	}
	//std::cout << "Trying to Bind Texture" << std::endl;
	shader->Update(this->getWorldTransform(), camera->getViewMatrix());
	texture->Bind(0);
	//std::cout << "Trying to draw game object" << std::endl;
	mesh->Draw();
}

glm::mat4 GameObject::getWorldTransform() {
	glm::mat4 world_transform = this->getTransform()->getModel();

	//this->calculated_transform = this->transform;
	GameObject* temp = parent;
	while (temp != nullptr) {
		world_transform = parent->getWorldTransform() * world_transform;
		/*this->calculated_transform.setScale(this->transform.getScale() * temp->getTransform().getScale());
		this->calculated_transform.setRotation(this->transform.getRotation() + temp->getTransform().getRotation());
		this->calculated_transform.setPosition(this->transform.getPosition() + temp->getTransform().getPosition());*/
		temp = temp->parent;
	}
	return world_transform;
	//return calculated_transform;
}

GameObject::~GameObject()
{
}
