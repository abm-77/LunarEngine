#include "Graphics/shader.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <gtc/type_ptr.hpp>

Shader::~Shader()
{
	glDeleteProgram(rendererID);
}

bool Shader::LoadFromFile(const std::string& filepath)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertex_file_path	= filepath + ".vs";
	std::string fragment_file_path	= filepath + ".fs";

	
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) 
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else 
	{
		printf("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ !\n", vertex_file_path.c_str());
		getchar();
		return false;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) 
	{
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ !\n", fragment_file_path.c_str());
		getchar();
		return false;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path.c_str());
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		return false;
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path.c_str());
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
		return false;
	}

	// Link the program
	printf("Linking program\n");
	rendererID = glCreateProgram();
	glAttachShader(rendererID, VertexShaderID);
	glAttachShader(rendererID, FragmentShaderID);
	glLinkProgram(rendererID);

	// Check the program
	glGetProgramiv(rendererID, GL_LINK_STATUS, &Result);
	glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(rendererID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		return false;
	}

	glDetachShader(rendererID, VertexShaderID);
	glDetachShader(rendererID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	
	return true;
}


void Shader::Bind() const
{
	glUseProgram(rendererID);
}
void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(rendererID, name), (int) value);
}
void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(rendererID, name), value);
}
void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(rendererID, name), value);
}

void Shader::SetVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(rendererID, name), x, y);
}
void Shader::SetVec2(const char* name, glm::vec2 v) const
{
	glUniform2f(glGetUniformLocation(rendererID, name), v.x, v.y);
}

void Shader::SetVec3(const char* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(rendererID, name), x, y, z);
}
void Shader::SetVec3(const char* name, glm::vec3 v) const
{
	glUniform3f(glGetUniformLocation(rendererID, name), v.x, v.y, v.z);
}

void Shader::SetVec4(const char* name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(rendererID, name), x, y, z, w);
}
void Shader::SetVec4(const char* name, glm::vec4 v) const
{
	glUniform4f(glGetUniformLocation(rendererID, name), v.x, v.y, v.z, v.w);
}

void Shader::SetMat4(const char* name, glm::mat4 v) const
{
	glUniformMatrix4fv(glGetUniformLocation(rendererID, name), 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::SetMaterial(const std::string& materialName, Material material) const
{
	SetVec3((materialName + ".emissive").c_str(), material.emissive);
	//SetVec3((materialName + ".diffuse").c_str(), material.diffuse);
	//SetVec3((materialName + ".specular").c_str(), material.specular);
	SetFloat((materialName + ".shininess").c_str(), material.shininess);
}

void Shader::SetLight(const std::string& lightName, Light light) const
{
	SetVec3((lightName + ".ambient").c_str(), light.ambient);
	SetVec3((lightName + ".diffuse").c_str(), light.diffuse);
	SetVec3((lightName + ".specular").c_str(), light.specular);
}

void Shader::SetDirectionalLight(const std::string& lightName, DirectionalLight light) const
{
	SetVec3((lightName + ".direction").c_str(),	light.direction);

	SetVec3((lightName + ".ambient").c_str(),	light.ambient);
	SetVec3((lightName + ".diffuse").c_str(),	light.diffuse);
	SetVec3((lightName + ".specular").c_str(),	light.specular);
}

void Shader::SetPointLight(const std::string& lightName, PointLight light) const
{
	SetVec3((lightName + ".position").c_str(), light.position);

	SetFloat((lightName + ".constant").c_str(), light.constant);
	SetFloat((lightName + ".linear").c_str(), light.linear);
	SetFloat((lightName + ".quadratic").c_str(), light.quadratic);

	SetVec3((lightName + ".ambient").c_str(), light.ambient);
	SetVec3((lightName + ".diffuse").c_str(), light.diffuse);
	SetVec3((lightName + ".specular").c_str(), light.specular);
}

void Shader::SetSpotLight(const std::string& lightName, SpotLight light) const
{
	SetVec3((lightName + ".position").c_str(), light.position);
	SetVec3((lightName + ".direction").c_str(), light.direction);

	SetFloat((lightName + ".cutoff").c_str(), light.cutoff);
	SetFloat((lightName + ".outerCutoff").c_str(), light.outerCutoff);

	SetFloat((lightName + ".constant").c_str(), light.constant);
	SetFloat((lightName + ".linear").c_str(), light.linear);
	SetFloat((lightName + ".quadratic").c_str(), light.quadratic);

	SetVec3((lightName + ".ambient").c_str(), light.ambient);
	SetVec3((lightName + ".diffuse").c_str(), light.diffuse);
	SetVec3((lightName + ".specular").c_str(), light.specular);
}


unsigned int Shader::GetUniform(const GLchar* uniformName)
{
	return glGetUniformLocation(rendererID, uniformName);
}
unsigned int Shader::GetAttrib(const GLchar* attribName)
{
	return glGetAttribLocation(rendererID, attribName);
}

unsigned int Shader::GetRendererID()
{
	return rendererID;
}
