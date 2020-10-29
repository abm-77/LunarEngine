#pragma once
#include <vector>
#include "Graphics/View.h"
#include "Entity/Actor.h"

struct UpdateEvent;
struct DrawEvent;

class Scene
{
public:

	Scene();

	virtual void OnBegin	(const SceneBeginEvent* SBE);
	virtual void OnUpdate	(const UpdateEvent* UE);
	virtual void OnDraw		(const DrawEvent* DE);

	virtual void End();

	void AddActor(Actor* actor);
protected:
	std::vector <Actor*> actors;
};

class SceneManager
{
public:
	SceneManager();
	void AddScene		(Scene* scene);
	void ChangeScene	(Scene* newScene);

	Scene* GetPreviousScene() const;
	Scene* GetCurrentScene() const;

private:
	
	std::vector<Scene*> scenes;
	Scene* previousScene;
	Scene* currentScene;


};