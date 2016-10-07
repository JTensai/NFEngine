#pragma once
#include "AssetManager.h"

//AssetManager::AssetManager() {}

Texture* AssetManager::getTexture(const std::string& name) {
	if (textures.find(name) != textures.end()) {
		return textures.at(name);
	}
	// texture not found, try to load it
	Texture* texture = new Texture(name);
	textures.insert({ name, texture });
	return texture;
}

Mesh* AssetManager::getMesh(const std::string& name) {
	if (meshes.find(name) != meshes.end()) {
		// found texture, return it
		return meshes.at(name);
	}
	// texture not found, try to load it
	Mesh* mesh = new Mesh(name);
	meshes.insert({ name, mesh });
	return mesh;
}
