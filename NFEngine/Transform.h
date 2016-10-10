#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\matrix_decompose.hpp>
#include <glm\gtx\string_cast.hpp>
#include <iostream>

class Transform
{
public:
	Transform() {}

	glm::mat4 getModel() const {
		return m_model;
	}

	void translate(glm::vec3 translation) {
		m_translation[3] += glm::vec4(translation, 0.f);
		updateModel();
	}

	void setTranslation(glm::vec3 translation) {
		m_translation[3] = glm::vec4(translation, 1.f);
	}

	glm::vec3 getTranslation() const {
		return m_translation[3];
	}


	void rotateX(float angle_radians) {
		m_rotation_euler += glm::vec3(1, 0, 0) * angle_radians;
		glm::mat4 rot_x = glm::mat4(1.f);
		// rotating around x
		/*
		{1, 0,     0 ,     0}
		{0, cos(), -sin(), 0}
		{0, sin(), cos(),  0}
		{0, 0,     0,      1}
		*/
		rot_x[1][1] = glm::cos(angle_radians);
		rot_x[1][2] = -glm::sin(angle_radians);
		rot_x[2][1] = glm::sin(angle_radians);
		rot_x[2][2] = glm::cos(angle_radians);
		m_rotation_x *= rot_x;
	}

	void setRotationX(float angle_radians) {
		m_rotation_euler += glm::vec3(1, 0, 0) * angle_radians;
		glm::mat4 rot_x = glm::mat4(1.f);
		// rotating around x
		/*
		{1, 0,     0 ,     0}
		{0, cos(), -sin(), 0}
		{0, sin(), cos(),  0}
		{0, 0,     0,      1}
		*/
		rot_x[1][1] = glm::cos(angle_radians);
		rot_x[1][2] = -glm::sin(angle_radians);
		rot_x[2][1] = glm::sin(angle_radians);
		rot_x[2][2] = glm::cos(angle_radians);
		m_rotation_x = rot_x;
	}

	void rotateXDegrees(float angle_degrees) {
		rotateX(glm::radians(angle_degrees));
	}

	void rotateY(float angle_radians) {
		m_rotation_euler += glm::vec3(0, 1, 0) * angle_radians;
		glm::mat4 rot_y = glm::mat4(1.f);
		// rotating around y
		/*
		{cos(),  0, sin(), 0}
		{0,      1, 0,     0}
		{-sin(), 0, cos(), 0}
		{0,      0, 0,     1}
		*/
		rot_y[0][0] = glm::cos(angle_radians);
		rot_y[0][2] = glm::sin(angle_radians);
		rot_y[2][0] = -glm::sin(angle_radians);
		rot_y[2][2] = glm::cos(angle_radians);
		m_rotation_y *= rot_y;
	}

	void setRotationY(float angle_radians) {
		m_rotation_euler += glm::vec3(0, 1, 0) * angle_radians;
		glm::mat4 rot_y = glm::mat4(1.f);
		// rotating around y
		/*
		{cos(),  0, sin(), 0}
		{0,      1, 0,     0}
		{-sin(), 0, cos(), 0}
		{0,      0, 0,     1}
		*/
		rot_y[0][0] = glm::cos(angle_radians);
		rot_y[0][2] = glm::sin(angle_radians);
		rot_y[2][0] = -glm::sin(angle_radians);
		rot_y[2][2] = glm::cos(angle_radians);
		m_rotation_y = rot_y;
	}

	void rotateYDegrees(float angle_degrees) {
		rotateY(glm::radians(angle_degrees));
	}

	void rotateZ(float angle_radians) {
		m_rotation_euler += glm::vec3(0, 0, 1) * angle_radians;
		glm::mat4 rot_z = glm::mat4(1.f);
		// rotating around z
		/*
		{cos(), -sin(), 0, 0}
		{sin(), cos(),  0, 0}
		{0,     0,      1, 0}
		{0,     0,      0, 1}
		*/
		rot_z[0][0] = glm::cos(angle_radians);
		rot_z[0][1] = -glm::sin(angle_radians);
		rot_z[1][0] = glm::sin(angle_radians);
		rot_z[1][1] = glm::cos(angle_radians);
		m_rotation_z *= rot_z;
	}

	void setRotationZ(float angle_radians) {
		m_rotation_euler += glm::vec3(0, 0, 1) * angle_radians;
		glm::mat4 rot_z = glm::mat4(1.f);
		// rotating around z
		/*
		{cos(), -sin(), 0, 0}
		{sin(), cos(),  0, 0}
		{0,     0,      1, 0}
		{0,     0,      0, 1}
		*/
		rot_z[0][0] = glm::cos(angle_radians);
		rot_z[0][1] = -glm::sin(angle_radians);
		rot_z[1][0] = glm::sin(angle_radians);
		rot_z[1][1] = glm::cos(angle_radians);
		m_rotation_z = rot_z;
	}

	void rotateZDegrees(float angle_degrees) {
		rotateZ(glm::radians(angle_degrees));
	}

	void rotate(float angle_radians, glm::vec3 rotation_axis) {
		// something should be done here to make sure rotation values are always "-180 < angle < 180" instead of being able to go in into foverer 360, 720, 1080...
		//m_rotation_euler += rotation_axis*angle_radians;

		if (rotation_axis.x > 0) {
			rotateX(angle_radians);
		}
		if (rotation_axis.y > 0) {
			rotateY(angle_radians);
		}
		if (rotation_axis.z > 0) {
			rotateZ(angle_radians);
		}
		updateModel();
	}

	void rotateDegrees(float angle_degrees, glm::vec3 rotation_axis) {
		rotate(glm::radians(angle_degrees), rotation_axis);
	}

	void setRotation(glm::vec3 euler_angles_degrees) {
		m_rotation_euler = glm::vec3(0.f);
		setRotationX(glm::radians(euler_angles_degrees.x));
		setRotationY(glm::radians(euler_angles_degrees.y));
		setRotationZ(glm::radians(euler_angles_degrees.z));
		updateModel();
	}

	glm::vec3 getRotationEulerDegrees() {
		return glm::degrees(m_rotation_euler);
	}


	// Handle Scale
	void scale(glm::vec3 scale) {
		m_scale[0][0] *= scale.x;
		m_scale[1][1] *= scale.y;
		m_scale[2][2] *= scale.z;
		m_scale[3][3] = 1.f;
		updateModel();
	}

	glm::vec3 getScale() {
		return glm::vec3(m_scale[0][0], m_scale[1][1], m_scale[2][2]);
	}

	void setScale(glm::vec3 scale) {
		m_scale[0][0] = scale.x;
		m_scale[1][1] = scale.y;
		m_scale[2][2] = scale.z;
		m_scale[3][3] = 1.f;
		updateModel();
	}

	glm::vec3 getForward() const {
		return getModel() * glm::vec4(0, 0, -1, 0);
		//return m_forward;
	}
	glm::vec3 getRight() const {
		//return glm::cross(m_forward, m_up);
		return getModel() * glm::vec4(1, 0, 0, 0);
		//return glm::rotateY(m_forward, (float)glm::radians(90.f));
	}
	glm::vec3 getUp() const {
		return getModel() * glm::vec4(0, 1, 0, 0);
	}

	~Transform() {};
private:

	void updateModel() {
		m_model = m_translation * m_rotation_z * m_rotation_y * m_rotation_x * m_scale;
	}

	glm::mat4 m_model = glm::mat4(1.f);

	glm::mat4 m_translation = glm::mat4(1.f);
	glm::mat4 m_rotation_x = glm::mat4(1.f);
	glm::mat4 m_rotation_y = glm::mat4(1.f);
	glm::mat4 m_rotation_z = glm::mat4(1.f);
	glm::mat4 m_scale = glm::mat4(1.f);
	glm::vec3 m_rotation_euler = glm::vec3(0.f);
};


