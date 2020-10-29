#pragma once
#include <vector>
#include "Graphics/texture2D.h"
#include <glm.hpp>

class Shader;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 TexCoords;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture2D*> textures;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture2D*>& textures);

	void Draw(const Shader& shader);

private:
	unsigned int VAO, EBO, VBO;

	void SetupMesh();
};