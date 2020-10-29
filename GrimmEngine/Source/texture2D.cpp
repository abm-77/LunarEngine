#include "Graphics/texture2D.h"
#include "System/logging.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Graphics/stb_image.h"


Texture2D::Texture2D()
{
	
}

Texture2D::Texture2D(TextureType type) : textureType(type){}

Texture2D::~Texture2D()
{
	stbi_image_free(imageData);
	glDeleteTextures(1, &rendererID);
}


bool Texture2D::LoadFromFile(const std::string& filepath)
{
	// Generate Texture
	glGenTextures(1, &rendererID);
	Bind();

	// Set Texture Parameters 
	Configure();

	imageData = stbi_load(filepath.c_str(), &width, &height, &nChannels, 0);
	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); /// JPG = RGB, PNG = RGBA
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		Logger::PrintError("Failed to load texture.");
		return false;
	}
	Unbind();
	return true;
}

void Texture2D::Bind(unsigned int slot)
{
	if (textureSlot != slot) 
		textureSlot = slot;

	glActiveTexture(textureSlot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture2D::Unbind() const
{
	glActiveTexture(textureSlot);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Configure()
{
	stbi_set_flip_vertically_on_load(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// Clamp to edge on S axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			// Clamp to edge on T axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// When magnifying image, use linear interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // When minifying the image, use a linear blend of two mipmaps, each filtered linearly
}

TextureType Texture2D::GetTextureType() const
{
	return textureType;
}

int Texture2D::GetWidth() const
{
	return width;
}
int Texture2D::GetHeight() const
{
	return height;
}
int Texture2D::GetNChannels() const
{
	return nChannels;
}

unsigned int Texture2D::GetTextureID() const
{
	return rendererID;
}

