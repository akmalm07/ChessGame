#include "pch.h"
#include "GraphicsHandlerAPI.h"

#include <iostream>


//std::vector<GLFWwindow*> GraphicsHandlerAPI::windows; 
 
GraphicsHandlerAPI::GraphicsHandlerAPI() = default;


//void GraphicsHandlerAPI::AddWindow(GLFWwindow * window)
//{
//	windows.push_back(window);
//}


void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}



bool GraphicsHandlerAPI::InitalizeAPIS()
{

	if (!glfwInit())
	{
		fprintf(stderr, "Error Initializing GLFW (Graphics : GraphicsHandlerAPI.cpp)");
		std::cin.get();
		glfwTerminate();
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow * window = glfwCreateWindow(100, 100, "Initialize Window", nullptr, nullptr);
	if (!window)
	{
		printf("Error creating GLFW window!");
		glfwDestroyWindow(window); 
		return false;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fprintf(stderr, "Error initializing GLEW  (Graphics : GraphicsHandlerAPI.cpp) : %s", glewGetErrorString(error));
		std::cin.get();
		glfwTerminate();
		exit(EXIT_FAILURE);
		return false;
	}

	const GLubyte* version = glGetString(GL_VERSION); 
	printf("OpenGL Version: %s\n", version);

	glEnable(GL_BLEND); 
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_DEPTH_TEST); 

	glfwDestroyWindow(window);

	printf("Initalized OpenGL, but not set current context to window");

    return true;
}


//void GraphicsHandlerAPI::DeleteWindow(GLFWwindow * window) 
//{
//	auto it = std::find(windows.begin(), windows.end(), window);
//
//	if (it != windows.end())
//	{
//
//		windows.erase(it);
//	}
//}


void GraphicsHandlerAPI::ShutdownAPIS() 
{

	glfwMakeContextCurrent(nullptr);
	glfwTerminate();

}



GraphicsHandlerAPI::~GraphicsHandlerAPI() = default;


