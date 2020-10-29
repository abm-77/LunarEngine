#pragma once
#include "Graphics/vertex_buffer.h"
#include "Graphics/vertex_buffer_layout.h"

class VertexArray
{

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);


private:
	unsigned int rendererID;

};