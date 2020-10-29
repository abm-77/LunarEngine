#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include <map>

#define GAMEPAD_AXIS_DEADZONE 0.2f

class Input
{

public:

	static float GetAxis(unsigned int joystick, unsigned int axis);
	static bool GetButtonPressed(unsigned int joystick, unsigned int button);
	static bool GetButtonReleased(unsigned int joystick, unsigned int button);
	static bool GetButtonDown(unsigned int joystick, unsigned int button);
	static void Update();	
	
private:
	static int currentGamepadButtons[GLFW_GAMEPAD_BUTTON_LAST];
	static int previousGamepadButtons[GLFW_GAMEPAD_BUTTON_LAST];
	static GLFWgamepadstate gamepadState;
};	
