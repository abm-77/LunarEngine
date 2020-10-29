#include "System/ResourceManager.h"

#include "Graphics/texture2D.h"
#include "Audio/Audio.h"
#include "Graphics/shader.h"

std::unordered_map<std::string, std::shared_ptr<Resource>> ResourceManager::resources;
const std::string ResourceManager::resourceDirectory = "D:/dev/c_stuff/GrimmEngine/Sandbox/Resources/";

void ResourceManager::LoadResources()
{
	Add<Texture2D>("Box_Texture", "Images/container2.png");
	Add<Shader>("Sprite_Unlit", "Shaders/sprite_unlit");
	Add<Shader>("Basic_Text", "Shaders/basic_text");
	Add<AudioSource>("Dope_Song", "Sounds/stuff.wav");
}

void ResourceManager::UnloadResources()
{
	resources.clear();
}

void ResourceManager::Remove(const std::string& resourceName)
{
	resources.erase(resourceName);
}

bool ResourceManager::Has(const std::string& resourceName)
{
	return (Get<Resource>(resourceName) != nullptr);
}

