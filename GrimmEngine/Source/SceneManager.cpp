#include "System/SceneManager.h"
#include "System/logging.h"
#include "System/EventSystem.h"


Scene::Scene()
{
	EventBus::Subscribe(this, &Scene::OnUpdate);
	EventBus::Subscribe(this, &Scene::OnDraw);
	EventBus::Subscribe(this, &Scene::OnBegin);
}

void Scene::OnBegin(const SceneBeginEvent* SBE)
{
	for (Actor* actor : actors)
	{
		//actor->Init();
	}
}



void Scene::OnUpdate(const UpdateEvent* UE)
{
	for (Actor* actor : actors)
	{
		//actor->Update(deltaTime);
	}
}

void Scene::OnDraw(const DrawEvent* DE)
{
	for (Actor* actor : actors)
	{
		//actor->Draw(view);
	}
}

void Scene::End()
{
	Logger::PrintMessage("Scene ending.", 2);
	int counter = 0;
	for (Actor* actor : actors)
	{
		counter++;
		actor->CleanUp();
		delete actor;
	}
	Logger::PrintMessage("Scene ended. " + std::to_string(counter) + " actors cleaned up.", 2);
}

void Scene::AddActor(Actor* actor)
{
	actors.push_back(actor);
}

SceneManager::SceneManager() : scenes(0), currentScene(nullptr), previousScene(nullptr)
{
}

void SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::ChangeScene(Scene* newScene)
{
	//previousScene = currentScene;
	currentScene = newScene;

	SceneBeginEvent* SBE = new SceneBeginEvent();
	EventBus::Publish(SBE);
	delete SBE;
}

Scene* SceneManager::GetCurrentScene() const
{
	return currentScene;
}
