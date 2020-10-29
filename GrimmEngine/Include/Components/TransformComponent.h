#pragma once
#include "Component.h"


class TransformComponent : public Component
{
public:
	TransformComponent() {}
	
	void Init() override {}
	void OnUpdate(const UpdateEvent* UE) override {}

	void OnDraw(const DrawEvent* DE) override {}

	void CleanUp() override {}

	void SetPosition(glm::vec2 pos)
	{
		position = pos;
	}

	void Translate(glm::vec2 moveVector)
	{
		position += moveVector;
	}

	glm::vec2 GetPosition() const
	{
		return position;
	}
private:
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;
};