#include "pch.h"
#include "Shaders.h"


#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
	texture1 = 0;
	texture2 = 0;
	uniformSquareColor = 0;
	//uniformSquareColorWhite = 0;
	//uniformIsBlackSquare = GL_FALSE; 
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const std::string& vertexLocation, const std::string& fragmentLocation)
{
	std::cout << "Here i am in the Create from file\n ";
	std::string vertexString = ReadFile(vertexLocation); 
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const std::string& fileLocation)
{
	std::cout << "Here i am in the read file\n ";

	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation.c_str()); 
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint Shader::GetTex0Location()
{
	return texture1;
}

//GLuint Shader::GetTex1Location()
//{
//	return texture2;
//}


//GLuint Shader::GetSquareColorBlackLocation()
//{
//	return uniformSquareColorBlack; 
//}

GLuint Shader::GetSquareColorLocation()
{
	return uniformSquareColor;
}


void Shader::CompileShader(const std::string& vertexCode, const std::string& fragmentCode)
{
	std::cout << "Here i am in the Compile Shader\n ";
	shaderID = glCreateProgram();     
	if (shaderID == 0)
		std::cout << "Here i am but the shader ID is 0!!!\n ";
	GLenum error = glGetError();

	if (error != GL_NO_ERROR) {
		switch (error) {
		case GL_INVALID_OPERATION:
			fprintf(stderr, "glCreateProgram: Invalid operation.");
			break;
		case GL_INVALID_VALUE:
			fprintf(stderr, "glCreateProgram: Invalid value.");
			break;
		default:
			fprintf(stderr, "glCreateProgram: Unknown error.");
			break;
		}
	}
	else {
		// Successfully created the program
		fprintf(stderr, "Program created successfully with ID: %d", shaderID);
	}
	//if (shaderID == 0)
	//{
	//	printf("Error creating shader program!\n");
	//	return;
	//}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s\n", eLog);
		return;
	}

	LinkingUniforms();
}





void Shader::LinkingUniforms()
{


	uniformProjection = glGetUniformLocation(shaderID, "projection");
	std::cout << "Projection - " << uniformProjection << std::endl; 

	uniformModel = glGetUniformLocation(shaderID, "model");
	std::cout << "Model - " << uniformModel << std::endl;

	texture1 = glGetUniformLocation(shaderID, "texture0");
	std::cout << "Texture - " << texture1 << std::endl;

	uniformSquareColor = glGetUniformLocation(shaderID, "squareColor"); 
	std::cout << "Square Color - " << uniformSquareColor << std::endl; 

	uniformIsTexValid = glGetUniformLocation(shaderID, "isTexValid");
	std::cout << "Texture Bool - " << uniformIsTexValid << std::endl;


	//uniformSquareColorBlack = glGetUniformLocation(shaderID, "squareColorBlack");

	//uniformSquareColorWhite = glGetUniformLocation(shaderID, "squareColorWhite"); 

	//uniformIsBlackSquare = glGetUniformLocation(shaderID, "isBlackSquare");

	//texture2 = glGetUniformLocation(shaderID, "texture2");
}



//GLboolean Shader::GetIsBlackLoacation()
//{
//	return uniformIsBlackSquare;
//}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}


GLuint Shader::GetModelLocation()
{
	return uniformModel;
}

GLuint Shader::IsTexValidLocation()
{
	return uniformIsTexValid;
}


//GLuint Shader::GetViewLocation()
//{
//	return uniformView;
//}



void Shader::LinkModelMatrix(glm::mat4& modelMatrix)
{
	//if (uniformModel == 0)
	//	printf("CRAZY MISTAKE");
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));  

}

void Shader::LinkProjectionMatrix(glm::mat4& projectionMatrix) 
{
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));   
}


void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	texture1 = 0;
	uniformSquareColor = 0;
	//uniformSquareColorWhite = 0;
	//uniformIsBlackSquare = GL_FALSE;
	uniformModel = 0;
	uniformProjection = 0;
}


void Shader::AddShader(GLuint theProgram, const std::string& shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode.c_str(); 

	GLint codeLength[1];
	codeLength[0] = shaderCode.length();

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	ClearShader();
}
