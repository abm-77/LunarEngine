#include "System/Application.h"
#include "Scenes/MainMenuScene.h"


int main(void)
{
	Window* window = new Window;
	Application application;

	application.SetWindow(window);
	application.Init();

	//window->Init("Game", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT); 
	window->GetSceneManager()->ChangeScene(new MainMenuScene);

	while (application.IsRunning())
	{
		// input
		application.Update();

		// render
		application.Render();
	}

	application.Close();
	
	return 0;
}

