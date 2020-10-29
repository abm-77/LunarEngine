#include "Graphics/element_buffer.h"
#include <glad/glad.h>
#include <glfw3.h>

ElementBuffer::ElementBuffer(const void* data, unsigned int ct) : count(ct)
{
	glGenBuffers(1, &rendererID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int ElementBuffer::GetBufferID()
{
	return rendererID;
}
