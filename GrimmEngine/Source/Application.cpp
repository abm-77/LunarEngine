#include "System/Application.h"
#include "Graphics/renderer.h"
#include "System/logging.h"
#include "Audio/Audio.h"
#include "System/EventSystem.h"

void Application::Init()
{
	glfwInit();

	AudioManager::Init();

	ApplicationInitEvent* IE = new ApplicationInitEvent("Game", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	EventBus::Publish(IE);
	delete IE;
	
	UE = new UpdateEvent(0.16f);
	
	
	running = true;

	Logger::PrintMessage("Application running.");
}


void Application::Update()
{
	float currentFrame = glfwGetTime();
	UE->deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	EventBus::Publish(UE);

	window->PollWindowEvents();
}

void Application::Render()
{
	Renderer::Clear();

	window->RenderWindow();

	glfwSwapBuffers(window->GetGLFWWindow());
}

void Application::Close()
{
	Logger::PrintMessage("Application closing.");
	window->Close();

	delete window;
	delete UE;

	AudioManager::Close();
	glfwTerminate();
	Logger::PrintMessage("Application closed.");
}

bool Application::IsRunning()
{
	return !glfwWindowShouldClose(window->GetGLFWWindow());
}

void Application::SetWindow(Window* wind)
{
	window = wind;
}
