#pragma once

#include "Graphics/shader.h"
#include <glm.hpp>
#include "Graphics/texture2D.h"
#include "Graphics/View.h"
#include <memory>

class Sprite
{
public:
	Sprite(const Shader& shader);
	Sprite();

	void Draw(View* view, glm::vec2 position);
	
	glm::mat4 GetModelMatrix() const;

	int GetSpriteWidth() const;
	int GetSpriteHeight() const;
	int GetSourceWidth() const;
	int GetSourceHeight() const;

	void UpdateDimensions();


	void SetImageSource(const std::string& resourceName);
	void SetShader(std::shared_ptr<Shader> shader);
	void SetScale(glm::vec2 newscale);
	void SetOrigin(glm::vec2 neworigin);
	void SetRotation(float rot);
	void SetColor(glm::vec3 col);

private:
	unsigned int quadVAO, quadVBO;
	
	std::shared_ptr<Shader> spriteShader;

	glm::vec2 scale = glm::vec2(1.0f);
	float rotation = 0.0f;
	glm::vec2 origin = glm::vec2(0.5f, 0.5f);

	glm::vec3 color = glm::vec3(1.0f);


	std::shared_ptr<Texture2D> spriteTexture;
	int spriteWidth, spriteHeight;

	glm::mat4 modelMatrix;
};
