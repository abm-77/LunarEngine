#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm.hpp>
#include <map>
#include <string>
#include "Graphics/shader.h"
#include "Graphics/View.h"

struct Character 
{
	unsigned int textureID;
	glm::ivec2 size; 
	glm::ivec2 bearing; 
	unsigned int advance;
};


class TextRenderer 
{ 
public:

	TextRenderer();
	void Init();  
	void RenderText(View* view, const std::string& string, float x, float y, float scale, glm::vec3 color);


private:

	unsigned int VAO, VBO;

	std::map<char, Character> characters;
	std::shared_ptr<Shader> textShader;
	
};