#include "Graphics/View.h"
#include <gtc/matrix_transform.hpp>
#include "Graphics/shader.h"

View::View()
	: projectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)), viewMatrix(1.0f), position(glm::vec3(0))
{
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

View::View(ViewBounds bounds)
	: projectionMatrix(glm::ortho(bounds.left, bounds.right, bounds.bottom, bounds.top, -1.0f, 1.0f)), viewMatrix(1.0f),  position(glm::vec3(0)), bounds(bounds)
{
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void View::SetPosition(const glm::vec3& pos)
{
	position = pos;
	RecalculateViewMatrix();
}

void View::SetRotation(float rot)
{
	rotation = rot;
	RecalculateViewMatrix();
}

void View::Translate(glm::vec3 moveVector)
{
	position += moveVector;
	RecalculateViewMatrix();
}

ViewBounds View::GetViewBounds() const
{
	return bounds;
}


glm::vec3& View::GetPosition()
{
	return position;
}

glm::mat4 View::GetProjectionMatrix() const
{
	return projectionMatrix;
}

glm::mat4 View::GetViewMatrix() const
{
	return viewMatrix;
}

glm::mat4 View::GetViewProjectionMatrix() const
{
	return viewProjectionMatrix;
}

void View::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3 (0.0f, 0.0f, 1.0f));

	viewMatrix = glm::inverse(transform);

	viewProjectionMatrix = projectionMatrix * viewMatrix;

}
