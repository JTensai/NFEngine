#include "Texture.h"  
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& file_name = "./res/default.png")
{
	int width, height, num_components;
	unsigned char* image_data = stbi_load(file_name.c_str(), &width, &height, &num_components, 4);

	if (image_data == NULL) {
		std::cerr << "Texture loading failed for texture: " << file_name << std::endl;
		// couldn't load given image, use default
		image_data = stbi_load(((std::string)"./res/default.png").c_str(), &width, &height, &num_components, 4);
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	stbi_image_free(image_data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
