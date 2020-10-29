#pragma once
#include "System/SceneManager.h"
#include "Entities/Player.h"
#include "Graphics/TextRenderer.h"
#include "System/Input.h"
#include "System/EventSystem.h"
#include <iostream>
class MainMenuScene : public Scene
{
public:
	~MainMenuScene()
	{
		delete tr;
	}
	void OnBegin(const SceneBeginEvent* SBE) override
	{
		tr = new TextRenderer;
		tr->Init();
	}

	void OnUpdate (const UpdateEvent* UE) override
	{
		if (Input::GetButtonPressed(GLFW_JOYSTICK_1, GLFW_GAMEPAD_BUTTON_DPAD_DOWN))
			selectionIndex++;
		else if (Input::GetButtonPressed(GLFW_JOYSTICK_1, GLFW_GAMEPAD_BUTTON_DPAD_UP))
			selectionIndex--;

		selectionIndex = glm::clamp(selectionIndex, 0, 2);

		if (Input::GetButtonPressed(GLFW_JOYSTICK_1, GLFW_GAMEPAD_BUTTON_A))
		{

			switch (selectionIndex)
			{
			case 0: 
				// Start Game
				break;
			case 1: 
				// Option Menu
				break;
			case 2:
				// End Game
				break;
			}
		}
	}
	void OnDraw(const DrawEvent* DE) override
	{
		for (int i = 0; i < 3; i++)
		{
			if (selectionIndex == i)
				tr->RenderText(DE->view, menuOptions[i], (-48 * (std::strlen(menuOptions[i].c_str()) / 2.0f)) / 2.0f, -(i * 60), 1.0f, selectColor);
			else
				tr->RenderText(DE->view, menuOptions[i], (-48 * (std::strlen(menuOptions[i].c_str()) / 2.0f)) / 2.0f, -(i * 60), 1.0f, defaultColor);
		}
	}

	void End() override
	{
		Scene::End();
	}

private:
	TextRenderer* tr;
	const std::string menuOptions[3] = { "Start", "Options", "Quit" };
	int selectionIndex = 0;
	glm::vec3 defaultColor = { 1.0f, 1.0f, 1.0f };
	glm::vec3 selectColor = { 1.0f, 0.0f, 0.0f };
};
