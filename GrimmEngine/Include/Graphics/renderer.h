#pragma once

#include "Graphics/vertex_array.h"
#include "Graphics/element_buffer.h"
#include "Graphics/shader.h"

class Renderer 
{
public:

	static void Clear();
	static void Draw(const VertexArray& VA, const ElementBuffer& EB, const Shader& Shader);

private:

};
