#include "Timer.h"
#include <glad/glad.h>
#include <glfw3.h>

void Timer::Start()
{
	startTime = glfwGetTime();
}

void Timer::Pause()
{
	paused = true;
	pausedStartTime = glfwGetTime();
}

void Timer::Unpause()
{
	paused = false;
	totalPausedTime += pausedTime;
}

void Timer::Reset()
{
	startTime = 0;
	elapsedTime = 0;
	pausedTime = 0;
	pausedStartTime = 0;
	totalPausedTime = 0;
}

void Timer::Tick()
{
	if (paused)
		pausedTime = glfwGetTime() - pausedStartTime;
	else
		elapsedTime = glfwGetTime() - startTime - totalPausedTime;
}

double Timer::GetElapsed()
{
	return elapsedTime;
}

bool Timer::IsPaused()
{
	return paused;
}


