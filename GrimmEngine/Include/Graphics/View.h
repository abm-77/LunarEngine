#pragma once
#include <glm.hpp>
#include "Graphics/shader.h"

struct ViewBounds
{
	float left;
	float right;
	float bottom;
	float top;
};

class View
{

public:

	View();
	View(ViewBounds bounds);
	
	void SetPosition(const glm::vec3& pos);
	void SetRotation(float rot);

	void Translate(glm::vec3 moveVector);

	ViewBounds GetViewBounds() const;

	glm::vec3& GetPosition();
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const;


	void RecalculateViewMatrix();


private:
	ViewBounds bounds;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 viewProjectionMatrix;

	float rotation = 0.0f;

	glm::vec3 position;


};