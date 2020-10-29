#include "Graphics/vertex_buffer.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "System/logging.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{											
	glGenBuffers(1, &rendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererID);
	
}


void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::GetBufferIndex()
{
	return rendererID;
}
