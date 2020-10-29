#include "Graphics/SpriteRenderer.h"
#include "System/ResourceManager.h"
#include <gtc/matrix_transform.hpp>

Sprite::Sprite() 
{ 
    spriteShader = ResourceManager::Get<Shader>("Sprite_Unlit");

    // Sprite quad data : setup as a vec4, first 2 floats pos, second 2 floats texcoords
    float vertices[] =
    {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };


    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void Sprite::Draw(View* view, glm::vec2 position)
{
    spriteShader->Bind();

	// Translate matrix
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));

	// Rotate matrix
    SetRotation(rotation);

    SetScale(scale);

	spriteShader->SetVec3("spriteColor", color);

    spriteTexture->Bind();

    glBindVertexArray(this->quadVAO);

    spriteShader->SetMat4("MVP", view->GetViewProjectionMatrix() * modelMatrix);
    spriteShader->SetInt("image", 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

glm::mat4 Sprite::GetModelMatrix() const
{
    return modelMatrix;
}

void Sprite::UpdateDimensions()
{
    spriteWidth = spriteTexture->GetWidth() * scale.x;
    spriteHeight = spriteTexture->GetHeight() * scale.y;
}

void Sprite::SetImageSource(const std::string& resourceName)
{
    spriteTexture = ResourceManager::Get<Texture2D>(resourceName);
    UpdateDimensions();
}

void Sprite::SetShader(std::shared_ptr<Shader> shader)
{
    spriteShader = shader;
}

void Sprite::SetScale(glm::vec2 newscale)
{
    scale = newscale;
    UpdateDimensions();
    modelMatrix = glm::scale(modelMatrix, glm::vec3(spriteWidth, spriteHeight, 1.0f));
}

void Sprite::SetOrigin(glm::vec2 neworigin)
{
    origin = neworigin;
    SetRotation(rotation);
}

void Sprite::SetRotation(float rot)
{
    rotation = rot;
    modelMatrix = glm::translate(modelMatrix, glm::vec3(origin.x * spriteWidth, origin.y * spriteHeight, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-origin.x * spriteWidth, -origin.y * spriteHeight, 0.0f));
}

void Sprite::SetColor(glm::vec3 col)
{
    color = col;
}

