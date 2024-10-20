#include "pch.h"
#include "Window.h" 
#include <iostream>

#include "GLFW/glfw3.h"



bool Window::numOfInits;


Window::Window()
{

	for (auto& mod : mods)
	{
		mod = Mods::EMPTY; 
	}

	numOfInits = true;

	name = "";

	whichTimePressed = false;

	mainWindow = nullptr;

	bufferWidth = 0; 
	bufferHeight = 0;

	width = 800;
	height = 800;
	
	chessSquareWidth = width / 8;
	chessSquareHeight = height / 8;

	mouseCurrentX = 0;
	mouseCurrentY = 0;


	mouseBeforeX = 0.0;
	mouseBeforeY = 0.0;

	mouseAfterX = 0.0;
	mouseAfterY = 0.0;

	leftOrtho = 0.0f; 
	rightOrtho = 0.0f; 
	topOrtho = 0.0f; 
	bottomOrtho = 0.0f;


	for (int i = 0; i < 2; i++)
	{
		mouseButtons[i].function = nullptr;
		mouseButtons[i].pressed = false;
	}


	for (size_t i = 0; i < 1024; i++) 
	{
		keys[i] = 0; 
	} 

}

Window::Window(GLint windowWidth, GLint windowHeight, std::string_view name) 
{
	//numOfInits = true;

	whichTimePressed = false;


	for (auto& mod : mods)
	{
		mod = Mods::EMPTY;       
	}

	this->name = name; 

	mainWindow = nullptr;

	bufferWidth = 0;
	bufferHeight = 0;

	width = windowWidth;
	height = windowHeight;

	chessSquareWidth = width / 8;
	chessSquareHeight = height / 8;

	mouseCurrentX = 0;
	mouseCurrentY = 0;

	mouseBeforeX = 0.0;
	mouseBeforeY = 0.0;
	
	mouseAfterX = 0.0;
	mouseAfterY = 0.0;


	for (int i = 0; i < 2; i++)
	{
		mouseButtons[i].function = nullptr;
		mouseButtons[i].pressed = false; 
	}

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}


	float aspectRatio = windowWidth / windowHeight;

	if (aspectRatio >= 1.0f)
	{
		leftOrtho = -1.0f * aspectRatio;
		rightOrtho = 1.0f * aspectRatio;
		topOrtho = 1.0f;
		bottomOrtho = -1.0f;
	}
	else
	{
		leftOrtho = -1.0f;
		rightOrtho = 1.0f;
		topOrtho = 1.0f / aspectRatio;
		bottomOrtho = -1.0f / aspectRatio;
	}
}


//
//void Window::RunTempLoop(std::promise<bool>& didTrans)
//{
//	while (glfwWindowShouldClose(mainWindow))
//	{
//		glfwPollEvents();
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		std::this_thread::sleep_for(std::chrono::seconds(1));
//		printf("Hello From Window Class");
//
//		glfwSwapBuffers(mainWindow);
//
//		if (didTransfer == true)
//		{
//			break;
//		}
//	}



bool Window::CreateWindow()
{

	mainWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (!mainWindow)  
	{
		printf("Error creating GLFW window!");  
		ClearWindow(); 
		return false; 
	}

	glfwSetErrorCallback([](int error, const char* description) 
	{
		fprintf(stderr, "GLFW Error: %s\n", description);
	});

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	CreateCallbacks();

	glfwSwapInterval(1);

	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);




	return true;
}


//void Window::TransferLoop(std::function<void(GLFWwindow *)> newLoopHandler) 
//{
//	didTransfer = true;
//
//	newLoopHandler(mainWindow);
//}



void Window::SetShouldClose(bool trueOrFalse)
{
	return glfwSetWindowShouldClose(mainWindow, (trueOrFalse ? GLFW_TRUE : GLFW_FALSE) );
}
 

std::array<bool, 1024> Window::GetKeys() 
{
	return keys; 
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(mainWindow);
}
 

Mods Window::FindTheModeValue(unsigned int mode)
{
	switch (mode)
	{
	case GLFW_MOD_CONTROL:
		return Mods::CONTROL;

	case GLFW_MOD_ALT: 
		return Mods::ALT; 

	case GLFW_MOD_SHIFT: 
		return Mods::SHIFT; 

	case GLFW_MOD_SUPER:
		return Mods::SUPER;
	default:
		return Mods::EMPTY;

	}
}

void Window::setMouseBeforeX(double posX)
{
	mouseBeforeX = posX;
}


void Window::setMouseBeforeY(double posY)
{
	mouseBeforeY = posY;
}


void Window::setMouseAfterX(double posX)
{
	mouseAfterX = posX;
}
 

void Window::setMouseAfterY(double posY)
{
	mouseAfterY = posY;
}


void Window::setKey(unsigned int key, bool val) 
{
	keys[key] = val;
}



const std::string Window::TranslateCoordinatesToNotation(uint32_t rank, uint32_t file) 
{

	if (file > 7 || rank > 7)
	{
		printf("File and rank must be between 0 and 7. (Window.cpp TranslateCoordinatesToNotation function)");
		std::cin.get();
		return "";
	}

	char fileChar = 'a' + file;  
	char rankChar = '1' + rank;  

	// Return the combined string as a chess square (like "a1", "h8", etc.)
	return std::string(1, fileChar) + std::string(1, rankChar);

}





bool Window::GetIsMouseButtonPressed(MouseButton firstOrSecond)
{
	switch (firstOrSecond)
	{
	case MouseButton::LEFT:
		return mouseButtons[0].pressed;

	case MouseButton::RIGHT: 
		return mouseButtons[1].pressed;
	}
}

void Window::SetWhichTimePressed(bool value)
{
	whichTimePressed = value;
}

bool Window::GetWhichTimePressed()
{
	return whichTimePressed;
}

std::string Window::GetName() 
{
	return name; 
}

double Window::GetMouseBeforeX()
{
	return mouseBeforeX;
}


double Window::GetMouseBeforeY()
{
	return mouseBeforeY;
}


double Window::GetMouseAfterX()
{
	return mouseAfterX;
}


double Window::GetMouseAfterY()
{
	return mouseAfterY;
}

bool Window::GetShouldClose() const
{
	return glfwWindowShouldClose(mainWindow);
}


void Window::MakeWindowContextCurrent() 
{
	glfwMakeContextCurrent(mainWindow);
}




void Window::HandleKeys(int key, int code, int action, int mode) 
{
	std::string name;
	for (size_t i = 0; i != 1024; i++)
	{
		if (key != i && action != GLFW_PRESS)
		{
			continue;
		}

		keys[i] = true;
		
		KeyCombonation* keyCombo;
		switch (mode) 
		{
		case 0:
			keyCombo = FindKeyCombonation(std::to_string(key));

			if (keyCombo)
			{
				keyCombo->function();
			}

		case GLFW_MOD_CONTROL:
			keyCombo = FindKeyCombonation(std::to_string(ToInt(Mods::CONTROL)) + " " + std::to_string(key));


			break;

		case GLFW_MOD_ALT:
			keyCombo = FindKeyCombonation(std::to_string(ToInt(Mods::ALT)) + " " + std::to_string(key));
			break;

		case GLFW_MOD_SHIFT:
			keyCombo = FindKeyCombonation(std::to_string(ToInt(Mods::SHIFT)) + " " + std::to_string(key));
			break;

		case GLFW_MOD_SUPER:
			keyCombo = FindKeyCombonation(std::to_string(ToInt(Mods::SUPER)) + " " + std::to_string(key));
			break;

		}	
		

		if (keyCombo) 
		{
			keyCombo->function();
		}
		break;


		if (action == GLFW_RELEASE) 
		{
			keys[i] = false;
		}

	}

}













void Window::HandleMouseCursor(double posX, double posY)
{
	if (mouseFirstMoved)
	{
		mouseBeforeX = posX;
		mouseBeforeY = posY;

		mouseFirstMoved = false;
	}

	mouseAfterX = posX - mouseBeforeX;
	mouseAfterY = mouseBeforeY - posY;

	mouseBeforeX = posX;
	mouseBeforeY = posY;


	mouseCurrentX = 7 - static_cast<uint32_t>(static_cast<double>(posY) / (height / 8));
	mouseCurrentY = 7 - static_cast<uint32_t>(static_cast<double>(posX) / (width / 8));

	//mouseCurrentX = static_cast<uint32_t>(static_cast<double>(posX) / (width / 8) );//orig: posX
	//mouseCurrentY = 7 - static_cast<uint32_t>(static_cast<double>(posY) / (height / 8));//orig: PosY 
}



void Window::HandleMouseButtons(int mouseButton, int action, int mods)
{
	switch (mouseButton)
	{
	case GLFW_MOUSE_BUTTON_LEFT: {
		switch (action)
		{
		case GLFW_PRESS: {

			const std::string& name = TranslateCoordinatesToNotation(mouseCurrentX, mouseCurrentY);

			std::cout << "\n\nNAME FROM HANDEL MUSE BUTTONS IS " << name << "\n\n";


			if (name.empty()) 
			{
				fprintf(stderr, "\nError: name is empty.\n");
			}
			WindowButton& button = FindWindowButtonName(name);  

			
			std::cout << "\n MouseCurrentX: " << mouseCurrentX << "\n"; 
			std::cout << " MouseCurrentY: " << mouseCurrentY << "\n";  
			std::cout << "\n buttonPosX: " << button.posX<< "\n"; 
			std::cout << " buttonPosY: " << button.posY << "\n"; 
			 
			bool result = false;
			if ((button.posX == mouseCurrentX && button.posY == mouseCurrentY) && button.function)
			{
				result = button.function(whichTimePressed, mouseCurrentX, mouseCurrentY); 
			}
			if (result)
				whichTimePressed = !whichTimePressed;

			mouseButtons[0].pressed = true;
			break;
		}//case of press


		case GLFW_RELEASE: {
			mouseButtons[0].pressed = false;
			break;
		}//case of release
		}
		break;
	}
			
	case GLFW_MOUSE_BUTTON_RIGHT: {
		switch (action)
		{
		case GLFW_PRESS: {
			mouseButtons[1].pressed = true;
			if (mouseButtons[1].function != nullptr)
				mouseButtons[1].function();
			break; }

		case GLFW_RELEASE: {
			mouseButtons[1].pressed = false;
			break; }

		default:
			// Handle unexpected actions if needed
			break;
		}
		break; }

	default:
		fprintf(stderr, "Problem with buttons because default was called for switch!");
		break;
	}
}


//void Window::HandleMouseButtons(int button, int action, int mods) 
//{
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//	{
//		mouseButtons[0] = true;
//	}
//	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//	{
//		mouseButtons[1] = true;
//	}
//	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//	{
//		mouseButtons[0] = false;
//	}
//	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//	{
//		mouseButtons[1] = false;
//	}
//
//}





//Private Functions

void Window::CreateCallbacks()
{
	//glfwSetWindowUserPointer(mainWindow, this); 
	glfwSetKeyCallback(mainWindow, m_HandleKeys);  
	glfwSetCursorPosCallback(mainWindow, m_HandleMouseCursor);  
	glfwSetMouseButtonCallback(mainWindow, m_HandleMouseButtons);  
}


//void Window::CreateCallbacks()
//{
//	glfwSetKeyCallback(mainWindow, m_HandleKeys);
//	glfwSetMouseButtonCallback(mainWindow, m_HandleMouseButtons);
//	glfwSetCursorPosCallback(mainWindow, m_HandleMouseCursor);
//}



void Window::m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	instance->HandleKeys(key, code, action, mode); 
}


void Window::m_HandleMouseCursor(GLFWwindow* window, double posX, double posY)
{
	Window* instence = static_cast<Window*>(glfwGetWindowUserPointer(window));

	instence->HandleMouseCursor(posX, posY);
}



void Window::m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods)
{
	Window* instence = static_cast<Window*>(glfwGetWindowUserPointer(window));

	instence->HandleMouseButtons(button, action, mods);
}




void Window::SetCursorLocked()
{
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::SetCursorNormal()
{
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
}


void Window::ClearWindow()
{

	if (!mainWindow)
	{
		mainWindow = nullptr;
		glfwDestroyWindow(mainWindow);
	}

	bufferWidth = 0;
	bufferHeight = 0;

	width = 0;
	height = 0;

	mouseBeforeX = 0.0;
	mouseBeforeY = 0.0;

	mouseAfterX = 0.0;
	mouseAfterY = 0.0;

	mouseCurrentX = 0;
	mouseCurrentY = 0;

	chessSquareWidth = 0;
	chessSquareHeight = 0;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	
	

	
	
	//GraphicsHandlerAPI::DeleteWindow(mainWindow);
}

Window::~Window()
{
	ClearWindow();
}






void Window::AddKeyCombonation(unsigned int keyNumber, std::function<void()> function)
{
	std::string name = std::to_string(keyNumber);

	keyCombonations[name] = KeyCombonation(keyNumber, function);
}

 
void Window::AddKeyCombonation(unsigned int keyNumber, Mods mode, std::function<void()> function) 
{
	std::string name = std::to_string(ToInt(mode)) + " " + std::to_string(keyNumber); 

	keyCombonations[name] = KeyCombonation(keyNumber, mode, function);
}



void Window::DelKeyCombonation(const std::string& keyNumber)
{
	if (keyCombonations.find(keyNumber) == keyCombonations.end())
	{
		fprintf(stderr, "Entered invalid window name ( Window.cpp : DelWindowButton )");
		return;
	}

	keyCombonations.erase(keyNumber); 
}


int Window::ToInt(Mods mod) 
{
	return static_cast<int>(mod);
}

Window::KeyCombonation * Window::FindKeyCombonation(const std::string& name)
{
	if (keyCombonations.find(name) == keyCombonations.end())
	{
		fprintf(stderr, "Entered invalid key number ( Window.cpp : FindKeyCombonation )");
		return nullptr;
	}

	return &keyCombonations[name];   
}



void Window::AddMouseCombonation(MouseButton firstOrSecond, std::function<void()> function)
{
	switch(firstOrSecond)
	{
	case MouseButton::LEFT:
		mouseButtons[0].function = function;
		break;
	case MouseButton::RIGHT:
		mouseButtons[1].function = function;
		break;
	}
}

void Window::DelMouseCombonation(MouseButton firstOrSecond) 
{
	switch (firstOrSecond) 
	{
	case MouseButton::LEFT: 
		mouseButtons[0].function = nullptr; 
		break;
	case MouseButton::RIGHT: 
		mouseButtons[1].function = nullptr; 
		break;
	}
}


void Window::AddWindowButton(unsigned int posX, unsigned int posY, float xCord, float yCord, float xSize, float ySize, std::function<bool(bool, unsigned int, unsigned int)> function, const std::string& name)
{
	if (posX > 7 || posY > 7)
	{
		fprintf(stderr, "Error: Invalid position for Chess Board ( Window.cpp : AddWindowButton )");
		return;
	}


	windowButtons.emplace(name, WindowButton(posX, posY, xCord, yCord, xSize, ySize, function));

	//if (windowButtons.find(name) != windowButtons.end())
	//{
	//	printf("\nCorrectly ADDED notation: %s", name.c_str());
	//}
}



void Window::DelWindowButton(const std::string& nameGiven)
{
	WindowButton& button = FindWindowButtonName(nameGiven);
	button = std::move(WindowButton());

	fprintf(stderr, "Entered invalid window name ( Window.cpp : DelWindowButton )");
	return;
}



Window::KeyCombonation::KeyCombonation()
{
	number = "";
	function = nullptr;
}


Window::KeyCombonation::KeyCombonation(unsigned int number, Mods mod, std::function<void()> function)
{
	this->number = number;

	this->mod = mod; 

	this->function = function; 
}

Window::KeyCombonation::KeyCombonation(unsigned int number, std::function<void()> function)
{
	this->number = number;

	this->mod = Mods::EMPTY; 

	this->function = function; 
}




Window::WindowButton::WindowButton()
{
	xCord = 0;
	yCord = 0;

	xSize = 0;
	ySize = 0;

	posX = 0;
	posY = 0;

}

Window::WindowButton::WindowButton(unsigned int posX, unsigned int posY, float xCord, float yCord, float xSize, float ySize, std::function<bool(bool, unsigned int, unsigned int)> function)
{
	this->xCord = xCord; 
	this->yCord = yCord;
	
	this->xSize = xSize; 
	this->ySize = ySize; 

	this->posX = posX;
	this->posY = posY;
	
	this->function = function;

}

Window::WindowButton::WindowButton(WindowButton&& other) noexcept
{	
	this->xCord = other.xCord;
	this->yCord = other.yCord;
	this->xSize = other.xSize;
	this->ySize = other.ySize;
	this->posX = other.posX;
	this->posY = other.posY;
	this->function = std::move(other.function);

	other.xCord = 0;
	other.yCord = 0;
	other.xSize = 0;
	other.ySize = 0;
	other.function = nullptr;
}



Window::WindowButton::WindowButton(const WindowButton& other) noexcept
{
	this->xCord = other.xCord;
	this->yCord = other.yCord;
	this->xSize = other.xSize;
	this->ySize = other.ySize;
	this->posX = other.posX;
	this->posY = other.posY;
	this->function = other.function;

}





Window::WindowButton& Window::WindowButton::operator=(Window::WindowButton&& other) noexcept
{ 
	if (this != &other)
	{
		this->xCord = other.xCord; 
		this->yCord = other.yCord; 
		this->xSize = other.xSize; 
		this->ySize = other.ySize; 
		this->function = std::move(other.function); 

		other.xCord = 0;
		other.yCord = 0;
		other.xSize = 0;
		other.ySize = 0;
		other.function = nullptr; 

	}

	return *this;
}





Window::WindowButton& Window::FindWindowButtonName(const std::string& name)
{


	auto it = windowButtons.find(name);  
	if (it != windowButtons.end()) 
	{
		std::cout << "\n\nAfter Calc posX " << it->second.posX << "";
		std::cout << "After Calc posY " << it->second.posY << "\n\n";


		return it->second; 
	}

	fprintf(stderr, "ERROR: The name provided does not exist! ( Window : FindWindowButtonName(const std::string &) )");

	//throw std::runtime_error("Window button not found: " + name);

}
