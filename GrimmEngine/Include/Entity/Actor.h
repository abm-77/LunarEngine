#pragma once
#include <vector>
#include "Graphics/View.h"

class Component;

struct UpdateEvent;
struct DrawEvent;
struct SceneBeginEvent;

class Actor
{

public:
	virtual void OnBegin(const SceneBeginEvent* SBE);
	virtual void OnUpdate(const UpdateEvent* UE);
	virtual void OnDraw(const DrawEvent* DE);
	virtual void CleanUp();

	void AddComponent(Component* component);
private:
	std::vector <Component*> components;
};