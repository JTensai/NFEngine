#include "Shader.h"
#include <iostream>
#include <fstream>

static std::string LoadShader(const std::string& file_name);
static void CheckShaderError(GLuint shader, GLuint flag, bool is_program, const std::string& error_message);
static GLuint CreateShader(const std::string& full_text_of_shader_program, GLenum shader_type);

// RENAME MODEL STUFF TO "MVP"

Shader::Shader(const std::string& file_name)
{
	// the shader program that we read in from the seperate file
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(file_name + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(file_name + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texture_coordinate");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::Update(const glm::mat4& world_transform, const glm::mat4& view_matrix) {
	glm::mat4 projection_matrix = view_matrix * world_transform;// .composeWorldSpaceMatrix();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &projection_matrix[0][0]);
}

static GLuint CreateShader(const std::string& full_text_of_shader_program, GLenum shader_type) {
	GLuint shader = glCreateShader(shader_type);

	if (shader == 0) {
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar* shader_source_strings[1];
	GLint shader_source_string_lengths[1];

	shader_source_strings[0] = full_text_of_shader_program.c_str();
	shader_source_string_lengths[0] = full_text_of_shader_program.length();

	glShaderSource(shader, 1, shader_source_strings, shader_source_string_lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string& file_name) {
	std::ifstream file;
	file.open((file_name).c_str());
	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader: " << file_name << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool is_program, const std::string& error_message) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (is_program) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (is_program) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << error_message << ": '" << error << "'" << std::endl;
	}
}



