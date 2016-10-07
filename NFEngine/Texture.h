#pragma once

#include <string>
#include <GLEW\glew.h>

class Texture
{
public:
	Texture(const std::string& file_name);
	Texture();
	virtual ~Texture();

	void Bind(unsigned int unit);
private:
	GLuint m_texture;
};

