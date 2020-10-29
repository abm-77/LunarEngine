#include "Entity/Actor.h"
#include "Components/Component.h"
#include "System/logging.h"
#include "System/EventSystem.h"

void Actor::OnBegin(const SceneBeginEvent* SBE)
{

}

void Actor::OnUpdate(const UpdateEvent* UE)
{
}

void Actor::OnDraw(const DrawEvent* view)
{

}

void Actor::CleanUp()
{
	Logger::PrintMessage("Actor clean up commenced.", 3);
	int counter = 0;
	for (Component* component : components)
	{
		counter++;
		component->CleanUp();
		delete component;
	}
	Logger::PrintMessage("Actor cleaned up. " + std::to_string(counter) + " components deleted.", 3);
}

void Actor::AddComponent(Component* component)
{
	components.push_back(component);
}
