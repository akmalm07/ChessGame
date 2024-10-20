#pragma once

#include "pch.h" 


class Game
{

public:
	//Game();

	Game(unsigned int windowHeight, unsigned int windowWidth); 


	void CreateShaders(const std::string& vertShader, const std::string& fragShader); 
	
	void InitalizeBoard(unsigned int winWidth, unsigned int winHeight, const std::string& name);

	void InitalizeMeshes();

	void AddPieces();

	//void InitalizePieces();

	void LoadTextures(); 

	void UseTextures(GLuint textureLocation, unsigned int posX, unsigned int posY); 

	void RenderBoard(GLuint squareColorUniform/*, GLuint squareColorWhiteUniform, GLuint isBlackSquareUniform, */, GLuint textureUniform, glm::mat4& modelMatrix); 

	void CreateWindow(unsigned int height, unsigned int width, const std::string& name); 

	void InitalizeBoardWindowButtons(const std::string& windowName);
	//
	//void Switch(Piece::Pieces instruction, std::function<void(int)> Func, unsigned int addFactor);  

	//void Switch(Piece::Pieces instruction, std::function<void()> Func1, std::function<void()> Func2, std::function<void()> Func3, 
	//	std::function<void()> Func4, std::function<void()> Func5, std::function<void()> Func6); 

	//void Initalise(unsigned int height, unsigned int width);


	//void CreateShaders(const std::string& vertShader, const std::string& fragShader); 
	 
	//void GameLoop(const Window& window); 
	
	void RunGame(unsigned int windowWidth, unsigned int windowHeight);


	void EndGame();


	~Game();
private:

	struct Player
	{
	public:

		void SwitchTurn() 
		{
			turn = !turn;
		}

		Colors color;

		bool turn;

	};


	void Clear();
	void Delete();

	void Initalize();
;


	std::unique_ptr<Shader> shaders;
	std::unordered_map<std::string, Window> windows;   

	std::array <std::unique_ptr<Mesh>, 64> meshesSquares;   
	std::vector <std::unique_ptr<Mesh>> meshesPieces;



	std::array<Player, 2> players;

	std::unordered_map<std::string, Texture> textures;

	Board board;  


	unsigned int posX, posY;


	const std::string vertFile = "../Shaders/shader.vert";
	const std::string fragFile = "../Shaders/shader.frag";


	
	
	
	
	//std::array<Pawn, 16> pawnList;   
	//std::array<Rook, 4> rookList;   
	//std::array<Knight, 4> knightList;  
	//std::array<Bishop, 4> bishopList;  
	//std::array<Queen, 2> queenList; 
	//std::array<King, 2> kingList;  


};

