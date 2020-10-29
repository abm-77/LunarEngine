#include "Graphics/Renderer.h"

void Renderer::Clear()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& VA, const ElementBuffer& EB, const Shader& Shader)
{
	VA.Bind();
	EB.Bind();
	Shader.Bind();

	glDrawElements(GL_TRIANGLES, EB.GetCount(), GL_UNSIGNED_INT, nullptr);

}


