#pragma once
#include <glad/glad.h>
#include <glfw3.h>

#include "System/window.h"

#define DEFAULT_WINDOW_WIDTH 896
#define DEFAULT_WINDOW_HEIGHT 504

class Application
{

public:

	void Init();
	void Update();
	void Render();
	void Close();

	bool IsRunning();

	void SetWindow(Window* wind);

private:
	bool running = false;
	Window* window;

	UpdateEvent* UE;

	float deltaTime = 0;
	float lastFrame = 0;
};