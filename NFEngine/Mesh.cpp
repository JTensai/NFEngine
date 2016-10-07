#include "Mesh.h"
#include <vector>
#include <iostream>

Mesh::Mesh(Vertex* verts, unsigned int num_verts, unsigned int* indices, unsigned int num_indices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < num_verts; i++) {
		model.positions.push_back(verts[i].getPosition());
		model.texCoords.push_back(verts[i].getTextureCoordinate());
		model.normals.push_back(verts[i].getNormal());
	}

	for (unsigned int i = 0; i < num_indices; i++) {
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);
}

Mesh::Mesh(const std::string& file_name) {

	std::cout << "Importing OBJ: " << file_name << std::endl;
	IndexedModel model = OBJModel(file_name).ToIndexedModel();

	std::cout << "Begin initializing model" << std::endl;
	InitMesh(model);
}

Mesh::Mesh() {

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertex_array_object);

}

void Mesh::Draw() {
	//std::cout << "Drawing mesh" << std::endl;
	glBindVertexArray(m_vertex_array_object);

	glDrawElements(GL_TRIANGLES, m_draw_count, GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);
	//std::cout << "Done drawing mesh" << std::endl;
}

void Mesh::InitMesh(const IndexedModel& model) {

	m_draw_count = model.indices.size();

	glGenVertexArrays(1, &m_vertex_array_object);
	glBindVertexArray(m_vertex_array_object);

	glGenBuffers(NUM_BUFFERS, m_vertex_array_buffers);

	// sizeof is a compile time function, so it can't know the size of verts, only a defined class

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() *sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[TEXTURE_COORDINATE_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() *sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertex_array_buffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);


	glBindVertexArray(0);
	std::cout << "model done initializing" << std::endl;
}