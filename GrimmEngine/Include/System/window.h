#pragma once

#include <glad/glad.h>
#include <glfw3.h>

#include "System/SceneManager.h"

struct UpdateEvent;
struct DrawEvent;
struct ApplicationInitEvent;

class Window
{

public:

	Window();
	void OnInit(const ApplicationInitEvent* IE);
	void OnUpdate(const UpdateEvent* UE);
	void RenderWindow();
	void Close();

	GLFWwindow* GetGLFWWindow();
	void GetWindowSize(int* width, int* height);
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	View* GetView();
	SceneManager* GetSceneManager() const;
	

	void PollWindowEvents();

private:
	GLFWwindow* window;
	SceneManager* sceneManager;
	View* view;

	DrawEvent* DE; 

	glm::vec2 aspectRatio = glm::vec2(16, 9);
	float scaleFactor = 560;
};

