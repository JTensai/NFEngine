#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "Mesh.h"

class AssetManager
{
public:
	static AssetManager& getAssetManager() {
		static AssetManager instance;
		return instance;
	}

	Texture* getTexture(const std::string& name);
	Mesh* getMesh(const std::string& name);

	unsigned int getNumTextures() { return textures.size(); }
	unsigned int getNumMeshes() { return meshes.size(); }

	// remove methods we specifically do not want this singleton to be able to do
	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;

private:
	AssetManager() {};

	std::map<std::string, Texture*> textures;
	std::map<std::string, Mesh*> meshes;
};

