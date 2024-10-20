#pragma once

#include "pch.h"

#include "Window.h"

#include <GLFW\glfw3.h>

class GraphicsHandlerAPI 
{
public:

	GraphicsHandlerAPI();

	//static void AddWindow(GLFWwindow * window);
	
	//static void DeleteWindow(GLFWwindow * window);

	static bool InitalizeAPIS();

	static void ShutdownAPIS();   

	~GraphicsHandlerAPI();

private:

	//static std::vector <GLFWwindow*> windows;  
	 
};

