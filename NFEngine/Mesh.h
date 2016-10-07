#pragma once
#include <string>
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "obj_loader.h"

class Vertex {
public:
	Vertex(const glm::vec3& position, const glm::vec2& texture_coordinate, const glm::vec3& normal = glm::vec3(0,0,0)) {
		this->position = position;
		this->texture_coordinate = glm::vec2(texture_coordinate.x, 1 - texture_coordinate.y);
		//this->texture_coordinate = texture_coordinate; // texture was upside down using this
		this->normal = normal;
	}

	inline glm::vec3 getPosition() { return position; }
	inline glm::vec2 getTextureCoordinate() { return texture_coordinate; }
	inline glm::vec3 getNormal() { return normal; }
private:
	glm::vec3 position;
	glm::vec2 texture_coordinate;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh(Vertex* verts, unsigned int num_verts, unsigned int* indicies, unsigned int num_indicies);
	Mesh(const std::string& file_name);
	Mesh();
	virtual ~Mesh();

	void Draw();
private:
	void InitMesh(const IndexedModel& model);

	enum {
		POSITION_VB,
		TEXTURE_COORDINATE_VB,
		NORMAL_VB,
		INDEX_VB,

		NUM_BUFFERS
	};
	GLuint m_vertex_array_object;
	GLuint m_vertex_array_buffers[NUM_BUFFERS];
	unsigned int m_draw_count;
};

