#include "Graphics/Camera.h"
#include <gtc/matrix_transform.hpp>


Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float roll, float zoom) : Forward (glm::vec3 (0, 0, -1))
{
	Position		= pos;
	Up				= up;
	Yaw				= yaw;
	Pitch			= pitch;
	Roll			= roll;
	Zoom			= zoom;

	CalculateCameraVectors();
}

void Camera::SetPosition(const glm::vec3& pos)
{
	Position = pos;
}

void Camera::Translate(glm::vec3 moveVector)
{
	Position += moveVector;
}

glm::vec3 Camera::GetPosition()
{
	return Position;
}

glm::vec3 Camera::GetForward()
{
	return Forward;
}

glm::vec3 Camera::GetUp()
{
	return Up;
}

glm::vec3 Camera::GetRight()
{
	return Right;
}

glm::vec3 Camera::GetWorldUp()
{
	return glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetViewMatrix()
{

	return glm::lookAt(Position, Position + Forward, Up);
}

float Camera::GetZoom()
{
	return Zoom;
}

void Camera::CalculateCameraVectors()
{
	glm::vec3 temp;
	temp.x		= cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	temp.y		= sin(glm::radians(Pitch));
	temp.z		= sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	Forward		= glm::normalize(temp);
	Right		= glm::normalize(glm::cross(Forward, GetWorldUp()));
	Up			= glm::normalize(glm::cross(Right, Forward));
}
