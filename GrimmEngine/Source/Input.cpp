#include "System/Input.h"
#include "System/logging.h"
#include <iostream>

int Input::currentGamepadButtons[];
int Input::previousGamepadButtons[];
GLFWgamepadstate Input::gamepadState;

float Input::GetAxis(unsigned int joystick, unsigned int axis)
{
	glfwGetGamepadState(joystick, &gamepadState);
	float axisValue = gamepadState.axes[axis];
	return (axisValue > GAMEPAD_AXIS_DEADZONE || axisValue < -GAMEPAD_AXIS_DEADZONE) ? axisValue : 0;
}

bool Input::GetButtonPressed(unsigned int joystick, unsigned int button)
{
	return currentGamepadButtons[button] && !previousGamepadButtons[button];
}

bool Input::GetButtonReleased(unsigned int joystick, unsigned int button)
{
	return !currentGamepadButtons[button] && previousGamepadButtons[button];
}

bool Input::GetButtonDown(unsigned int joystick, unsigned int button)
{
	return currentGamepadButtons[button];
}

void Input::Update()
{
	GLFWgamepadstate gamepadState;
	glfwGetGamepadState(0, &gamepadState);
	for (int i = 0; i < GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		previousGamepadButtons[i]	= currentGamepadButtons[i];
		currentGamepadButtons[i]	= gamepadState.buttons[i];
	}
}
