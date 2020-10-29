#pragma once
#include "Component.h"
#include "Graphics/SpriteRenderer.h"
#include "System/EventSystem.h"
 
class SpriteComponent : public Component
{
public:

	SpriteComponent() { sprite = new Sprite; }
	~SpriteComponent() { delete sprite; }

	void Init()  override {}

	void OnUpdate(const UpdateEvent* UE) override {}

	void OnDraw(const DrawEvent* DE)  override
	{
		sprite->Draw(DE->view, drawPosition);
	}

	void CleanUp()  override
	{
		delete sprite;
	}

	void SetDrawPosition(glm::vec2 pos)
	{
		drawPosition = pos;
	}

	void LoadSprite(const std::string& resourceName)
	{
		sprite->SetImageSource(resourceName);
	}

private:
	Sprite* sprite;
	glm::vec2 drawPosition;
};