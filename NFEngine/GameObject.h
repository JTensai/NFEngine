#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

class GameObject
{
public:
	GameObject();

	GameObject(const std::string& mesh_file_name, const std::string& texture_file_name = "./res/default.png");

	void GameObject::setParent(GameObject* parent);
	void GameObject::addChild(GameObject* child);
	void setMesh(const std::string& mesh);
	void setTexture(const std::string& file_name);
	virtual void primaryUpdate(float delta_seconds) final; // virtual + final makes it so no child class can override it
	virtual void draw(Shader* shader, Camera* camera) final;

	// should be overriden by child classes that need functionality in update
	virtual void update(float delta_seconds) {};

	Transform* getTransform() { return &transform; }
	void setTransform(Transform transform) { this->transform = transform; }

	glm::mat4 getWorldTransform();

	virtual ~GameObject();
protected:
	GameObject* parent;
	std::vector<GameObject*> children;
	Transform transform;
	Transform calculated_transform;
	Mesh* mesh;
	Texture* texture;

private:
};

