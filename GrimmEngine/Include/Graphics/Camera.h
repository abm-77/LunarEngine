#pragma once
#include <glm.hpp>

class Camera
{

public:
	
	Camera(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0), float yaw = -90.f, float pitch = 0.0f, float roll = 0.0f, float zoom = 45.0f);

	void SetPosition(const glm::vec3& pos);
	void Translate(glm::vec3 moveVector);

	glm::vec3 GetPosition();
	glm::vec3 GetForward();
	glm::vec3 GetUp();
	glm::vec3 GetRight();
	static glm::vec3 GetWorldUp();

	glm::mat4 GetViewMatrix();
	float GetZoom();
	
protected:
	float Yaw;
	float Pitch;
	float Roll;

	float Zoom;
	void CalculateCameraVectors();
private:
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;



};