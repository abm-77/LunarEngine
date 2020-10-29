#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 MVP;
uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main ()
{
	FragPos = vec3(ModelMatrix * vec4(aPosition, 1.0));
	Normal = mat3(NormalMatrix) * aNormal;
	TexCoords = aTexCoords;

	gl_Position = MVP * vec4(aPosition, 1.0);
}