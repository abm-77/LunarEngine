#pragma once
#include "Entity/Actor.h"

class TransformComponent;
class SpriteComponent;
struct UpdateEvent; 
struct DrawEvent;

class Player : public Actor
{
public:
	void OnBegin(const SceneBeginEvent* SBE) override;
	void OnUpdate(const UpdateEvent* UE) override;
	void OnDraw(const DrawEvent* DE) override;
	void CleanUp() override;

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
};