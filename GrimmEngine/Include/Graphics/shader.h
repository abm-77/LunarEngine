#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <glm.hpp>
#include <string>
#include "System/ResourceManager.h"


struct Material
{
	glm::vec3 emissive;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

struct Light
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct DirectionalLight : public Light
{
	glm::vec3 direction;
};

struct PointLight : public Light
{
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight : public Light
{
	glm::vec3 position;
	glm::vec3 direction;

	float cutoff;
	float outerCutoff;

	float constant;
	float linear;
	float quadratic;
};

class Shader : public Resource
{
public:
	~Shader();

	bool LoadFromFile (const std::string& filepath);

	void Bind() const;
	void Unbind() const;

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;

	void SetVec2(const char* name, float x, float y) const;
	void SetVec2(const char* name, glm::vec2 v) const;

	void SetVec3(const char* name, float x, float y, float z) const;
	void SetVec3(const char* name, glm::vec3 v) const;

	void SetVec4(const char* name, float x, float y, float z, float w) const;
	void SetVec4(const char* name, glm::vec4 v) const;

	void SetMat4(const char* name, glm::mat4 v) const;

	void SetMaterial(const std::string& materialName, Material material) const;
	
	void SetLight(const std::string& lightName,Light light) const;
	void SetDirectionalLight(const std::string& lightName, DirectionalLight light) const;
	void SetPointLight(const std::string& lightName, PointLight light) const;
	void SetSpotLight(const std::string& lightName, SpotLight light) const;

	unsigned int GetRendererID();
	unsigned int GetUniform(const GLchar* uniformName);
	unsigned int GetAttrib(const GLchar* attribName);

private:
	unsigned int rendererID;


};

