#include "Graphics/Mesh.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "Graphics/vertex_buffer.h"
#include "Graphics/vertex_buffer_layout.h"
#include "Graphics/shader.h"
#include "Graphics/renderer.h"

Mesh::Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds, const std::vector<Texture2D*>& texts)
	: vertices(verts), indices(inds), textures (texts)
{
	SetupMesh();
}

void Mesh::Draw(const Shader& shader)
{
	unsigned int diffuseIndex = 0;
	unsigned int specularIndex = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		
		std::string name = "material.";
		std::string slotIndex;

		if (textures[i]->GetTextureType() == TEXTURE_DIFFUSE) 
		{
			slotIndex = std::to_string(diffuseIndex++); 
			name += "diffuse";
		}
		else if (textures[i]->GetTextureType() == TEXTURE_SPECULAR)
		{
			slotIndex = std::to_string(specularIndex++);
			name += "specular";
		}
		
		shader.SetFloat((name + "[" + slotIndex + "]").c_str(), i);	
		glBindTexture(GL_TEXTURE_2D, textures[i]->GetTextureID());
	}
	glActiveTexture(GL_TEXTURE0);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
	
}
