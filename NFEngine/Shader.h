#pragma once
#include <string>
#include <GLEW\glew.h>
#include "Transform.h"

class Shader
{
public:
	Shader(const std::string& file_name);
	virtual ~Shader();

	void Bind();
	void Update(const glm::mat4&, const glm::mat4&);
private:
	static const unsigned int NUM_SHADERS = 2; // could replace with an enum

	enum {
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

