#include "Graphics/vertex_array.h"
#include <glad/glad.h>
#include <glfw3.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*) offset);	// Tell OpenGl how vertex data is being supplied
		glEnableVertexAttribArray(i);																							// Enable this vertex attribute
		
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	Unbind();

}
