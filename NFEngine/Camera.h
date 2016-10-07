#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtx\string_cast.hpp>
#include <iostream>
#include "Transform.h"
#include "InputManager.h"

class Camera //:
	//public GameObject
{
public:
	// TODO: maybe need to reimplement glm::perspective()?
	Camera::Camera(const glm::vec3& position, float fov, float aspect, float near_clippling_plane, float far_clipping_plane) {
		this->transform = Transform();
		this->transform.translate(position);
		this->transform.rotate(-100.f, getUp());

		//m_perspective_matrix = glm::perspective(fov, aspect, near_clippling_plane, far_clipping_plane); // would need to move this if the camera can be modified at run time
		updatePerspectiveMatrix(fov, aspect, near_clippling_plane, far_clipping_plane); // would need to move this if the camera can be modified at run time
		//m_position = position;
		//m_forward = glm::vec3(0, 0, 1);
		//m_up = glm::vec3(0, 1, 0);
		//transform.rotate(glm::degrees(y_angle * delta_seconds), glm::vec3(0, 1, 0));
		//rotateAroundY(glm::radians(-80.f));
	}
	
	void updatePerspectiveMatrix(float fovy, float aspect, float near_z, float far_z) {
		float first =  1.f / (aspect * tan(fovy / 2.f));
		float second = 1.f / tan(fovy / 2.f);

		float third = -(far_z + near_z) / (far_z - near_z);
		float fourth = -2.f * (near_z * far_z) / (far_z - near_z);

		m_perspective_matrix[0][0] = first;
		m_perspective_matrix[1][1] = second; 
		m_perspective_matrix[2][2] = third;
		m_perspective_matrix[2][3] = -1.f;
		m_perspective_matrix[3][2] = fourth;
		m_perspective_matrix[3][3] = 0;
	}

	// TODO: maybe need to reimplement glm::lookAt()?
	glm::mat4 Camera::getViewMatrix() const {
		return m_perspective_matrix * glm::lookAt(transform.getTranslation(), transform.getTranslation() + getForward(), getUp());
	}

	//// TODO: reimplement glm::rotate
	//void Camera::rotateAroundY(float angle_radians) {
	//	this->transform.rotate(glm::degrees(angle_radians), glm::vec3(0, 1, 0));
	//	//m_forward = glm::normalize(glm::rotate(m_forward, angle_radians, m_up));
	//}

	//// TODO: reimplement glm::rotate
	//void Camera::rotateAroundX(float angle_radians) {
	//	this->transform.rotate(glm::degrees(angle_radians), glm::vec3(1, 0, 0));
	//	//m_forward = glm::normalize(glm::rotate(m_forward, angle_radians, this->getRight()));
	//}

	//void Camera::translate(glm::vec3 translation) {
	//	//translation = m_forward * translation;
	//	//m_position += translation;
	//	transform.translate(translation);
	//	//this->transform.translate(translation);
	//	//std::cout << "Camera pos: " << glm::to_string(m_position) << std::endl;
	//}

	glm::vec3 Camera::getForward() const {
		return transform.getModel() * glm::vec4(0, 0, -1, 0);
		//return m_forward;
	}
	glm::vec3 Camera::getRight() const {
		//return glm::cross(m_forward, m_up);
		return transform.getModel() * glm::vec4(1, 0, 0, 0);
		//return glm::rotateY(m_forward, (float)glm::radians(90.f));
	}
	glm::vec3 Camera::getUp() const {
		return transform.getModel() * glm::vec4(0, 1, 0, 0);
	}
	
	void Camera::update(float delta_seconds) {

		glm::vec3 translation;
		float y_angle = 0.f;
		float x_angle = 0.f;
		if (input.w_pressed)
			translation += m_camera_move_speed * this->getForward();
		if (input.s_pressed)
			translation -= m_camera_move_speed * this->getForward();
		if (input.a_pressed)
			translation -= m_camera_move_speed * this->getRight();
		if (input.d_pressed)
			translation += m_camera_move_speed * this->getRight();
		if (input.r_pressed)
			translation += m_camera_move_speed * glm::vec3(0, 0.5f, 0);
		if (input.f_pressed)
			translation -= m_camera_move_speed * glm::vec3(0, 0.5f, 0);
		if (input.left_pressed)
			y_angle -= m_camera_rotate_speed;
		if (input.right_pressed)
			y_angle += m_camera_rotate_speed;
		if (input.up_pressed)
			x_angle -= m_camera_rotate_speed;
		if (input.down_pressed)
			x_angle += m_camera_rotate_speed;

		if (y_angle != 0)
			transform.rotate(y_angle * delta_seconds, glm::vec3(0, 1, 0));
		if (x_angle != 0)
			transform.rotate(x_angle * delta_seconds, glm::vec3(1, 0, 0));
		if (translation != glm::vec3(0.f))
			transform.translate(translation * delta_seconds);
	}

	virtual Camera::~Camera() {}
private:
	glm::mat4 m_perspective_matrix;
	//glm::vec3 m_right;
	//glm::vec3 m_forward;
	//glm::vec3 m_up;

	Transform transform;

	float m_camera_move_speed = 7.f;
	float m_camera_rotate_speed = 1.5f;

	InputManager& input = InputManager::getInputManager();
};

