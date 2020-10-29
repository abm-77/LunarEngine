#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include "System/ResourceManager.h"


enum TextureType
{
	TEXTURE_UNDEFINED,
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
	MAX_TEXTURE_TYPE
};

class Texture2D : public Resource
{
public:
	Texture2D();
	Texture2D(TextureType type);
	~Texture2D();

	bool LoadFromFile(const std::string&);

	void Bind(unsigned int slot = GL_TEXTURE0);
	void Unbind() const;

	void Configure();

	TextureType GetTextureType() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetNChannels() const;
	unsigned int GetTextureID() const ;
private:
	TextureType textureType;
	unsigned int textureSlot;
	int width, height, nChannels;
	unsigned char* imageData;
	unsigned int rendererID;
};