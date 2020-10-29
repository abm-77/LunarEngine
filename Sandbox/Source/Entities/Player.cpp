#include "Player.h"
#include "System/Input.h"
#include "System/EventSystem.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h" 


void Player::OnBegin(const SceneBeginEvent* SBE)
{
	transform = new TransformComponent;
	transform->SetPosition(glm::vec2(-200.0f, -200.0f));

	sprite = new SpriteComponent();
	sprite->LoadSprite("Box_Texture");
	sprite->SetDrawPosition(transform->GetPosition());

	AddComponent(transform);
	AddComponent(sprite);

	//Actor::OnBegin(SBE);
}

void Player::OnUpdate(const UpdateEvent* UE)
{
	glm::vec2 input(Input::GetAxis(GLFW_JOYSTICK_1, GLFW_GAMEPAD_AXIS_LEFT_X), -Input::GetAxis(GLFW_JOYSTICK_1, GLFW_GAMEPAD_AXIS_LEFT_Y));
	transform->Translate(10.0f * input);
	sprite->SetDrawPosition(transform->GetPosition());
}

void Player::OnDraw(const DrawEvent* DE)
{

}

void Player::CleanUp()
{
	Actor::CleanUp();
}
