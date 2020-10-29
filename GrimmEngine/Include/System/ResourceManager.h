#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class Resource
{
	virtual bool LoadFromFile(const std::string& filepath) = 0;
};

class ResourceManager
{
public:
	static void LoadResources();
	static void UnloadResources();

	template <typename T>
	static void Add(const std::string& resourceName, const std::string& filepath);

	static void Remove(const std::string& resourceName);
	static bool Has(const std::string& resourceName);

	template <typename T>
	static std::shared_ptr<T> Get(const std::string& resourceName);
	
private:
	static std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
	static const std::string resourceDirectory;
};

template<typename T>
inline void ResourceManager::Add(const std::string& resourceName, const std::string& filepath)
{
	auto it = resources.find(resourceName);
	if (it != resources.end())
	{
		printf("Resource already allocated.\n");
		return;
	}
	else
	{
		std::shared_ptr<T> resource = std::make_shared<T>();
		if (!resource->LoadFromFile((resourceDirectory + filepath).c_str()))
		{
			printf("Resource could not be loaded from file.\n");
			return;
		}
		else 
		{
			resources.insert(std::make_pair(resourceName, resource));
		}
	}
}

template<typename T>
std::shared_ptr<T> ResourceManager::Get(const std::string& resourceName)
{
	auto it = resources.find(resourceName);

	if (it != resources.end()) return std::dynamic_pointer_cast<T>(it->second);

	return nullptr;
}
