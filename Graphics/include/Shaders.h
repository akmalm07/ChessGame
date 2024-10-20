#pragma once

#include "pch.h"

#include <fstream>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const std::string& vertexLocation,const  std::string& fragmentLocation);

	std::string ReadFile(const std::string& fileLocation);

	GLuint GetTex0Location(); 
	//GLuint GetTex1Location(); 

	//GLuint GetSquareColorWhiteLocation();
	GLuint GetSquareColorLocation();

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	GLuint IsTexValidLocation();

	void LinkModelMatrix(glm::mat4& modelMatrix);
	void LinkProjectionMatrix(glm::mat4& projectionMatrix);

	void UseShader();

	void ClearShader();

	~Shader();

private:
	GLuint shaderID; 
	GLuint uniformProjection, uniformModel,/* uniformView uniformSquareColorBlack,*/ uniformSquareColor, texture1, texture2, uniformIsTexValid;

	void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);
	void AddShader(GLuint theProgram, const std::string& shaderCode, GLenum shaderType);
	
	void LinkingUniforms(); 
};
