#pragma once

#include "pch.h"

#include "Definitions.h" 



struct GLFWwindow;



class Window
{
private:
	struct WindowButton;
	struct KeyCombonation; 

public:
	Window();

	Window(GLint windowWidth, GLint windowHeight, std::string_view name);
	
	bool CreateWindow();  

//	void TransferLoop(std::function<void(GLFWwindow *)> newLoopHandler);  

//	void RunTempLoop();

	void AddKeyCombonation(unsigned int keyNumber, std::function<void()> function);
	void AddKeyCombonation(unsigned int keyNumber, Mods mode, std::function<void()> function);
	void DelKeyCombonation(const std::string& keyNumber);

	void AddMouseCombonation(MouseButton firstOrSecond, std::function<void()> function); 
	void DelMouseCombonation(MouseButton firstOrSecond); 

	void AddWindowButton(unsigned int posX, unsigned int posY, float xCord, float yCord, float xSize, float ySize, std::function<bool(bool, unsigned int, unsigned int)> function, const std::string& name);
	void DelWindowButton(const std::string& name);

	void MakeWindowContextCurrent();

	void SetCursorLocked();
	void SetCursorNormal(); 

	inline GLint GetBufferWidth() const 
	{
		return bufferWidth;
	}

	inline GLint GetBufferHeight() const
	{
		return bufferHeight;
	}

	inline GLFWwindow* GetWindow() const
	{
		return mainWindow;
	}

	inline GLint GetWidth() const
	{
		return width;
	}

	inline GLint GetHeight() const
	{
		return height;
	}



	inline int GetLeftOrtho() const 
	{
		return leftOrtho;
	}


	inline int GetRightOrtho() const
	{
		return rightOrtho;
	}


	inline int GetTopOrtho() const
	{
		return topOrtho;
	}


	inline int GetBottomOrtho() const
	{
		return bottomOrtho;
	}


	bool GetIsMouseButtonPressed(MouseButton firstOrSecond);  

	bool GetWhichTimePressed();
	void SetWhichTimePressed(bool value);

	std::string GetName();

	double GetMouseBeforeX();
	double GetMouseBeforeY();

	double GetMouseAfterX();
	double GetMouseAfterY();

	bool GetShouldClose() const;

	void SetShouldClose(bool trueOrFalse);


	std::array<bool, 1024> GetKeys();

	void SwapBuffers() const;

	void ClearWindow();

	void HandleKeys(int key, int code, int action, int mode);
	void HandleMouseCursor(double posX, double posY);
	void HandleMouseButtons(int mouseButton, int action, int mods);

	~Window();

private:


	bool didTransfer; 

	static bool numOfInits;

	bool whichTimePressed;

	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	uint32_t chessSquareWidth, chessSquareHeight;  

	double mouseBeforeX;
	double mouseBeforeY;

	uint32_t mouseCurrentX; 
	uint32_t mouseCurrentY; 

	double mouseAfterX;
	double mouseAfterY;

	bool mouseFirstMoved;

	float leftOrtho, rightOrtho, topOrtho, bottomOrtho;


	struct WindowButton
	{
	public:

		WindowButton();

		WindowButton(unsigned int posX, unsigned int posY, float xCord, float yCord, float xSize, float ySize, std::function<bool(bool, unsigned int, unsigned int)> function);

		WindowButton(WindowButton&& other) noexcept;

		WindowButton(const WindowButton&) noexcept;

		WindowButton& operator=(const WindowButton&) = delete;

		WindowButton& operator=(WindowButton&& other) noexcept;

		unsigned int posX;
		unsigned int posY;
		float xCord;
		float yCord;
		float xSize;
		float ySize;
		std::function<bool(bool whichTimeIsPressed, unsigned int posX, unsigned int posY)> function;  
	};


	struct KeyCombonation
	{
	public:
		KeyCombonation();

		KeyCombonation(unsigned int name, std::function<void()> function);
		KeyCombonation(unsigned int name, Mods mod, std::function<void()> function);

		std::string number;

		Mods mod;
		
		std::function<void()> function;

	};


	struct mouseButton
	{
	public:
		std::function<void()> function;
		bool pressed;
	};

	std::string name;

	std::unordered_map <std::string, KeyCombonation> keyCombonations;   

	std::unordered_map <std::string, WindowButton > windowButtons; 


	std::array<bool, 1024> keys;
	std::array<Mods, 4> mods;
	
	std::array<mouseButton, 2> mouseButtons;


	int ToInt(Mods mod);

	KeyCombonation * FindKeyCombonation(const std::string& keyNumber);


	Mods FindTheModeValue(unsigned int mode);

	void setMouseBeforeX(double posX);
	void setMouseBeforeY(double posY);

	void setMouseAfterX(double posX); 
	void setMouseAfterY(double posY);
	WindowButton& FindWindowButtonName(const std::string& name);

	void setKey(unsigned int key, bool val); 

	const std::string TranslateCoordinatesToNotation(uint32_t rank, uint32_t file);

	void CreateCallbacks();
	static void m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void m_HandleMouseCursor(GLFWwindow* window, double posX, double posY); 
	static void m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods); 

//	void RunTempLoop(std::promise<bool>& didTrans); 


};






