#pragma once

#include "pch.h"

#include "BoardLayout.h"
#include "PieceBase.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#include "../Graphics/include/Window.h"

#include <GL/glew.h>



#include <glm/glm.hpp>



class Board : BoardLayout  
{
public:

	Board();

	Board(unsigned int winWidth, unsigned int winHeight, float blackR, float blackG, float blackB, float blackAlpha, float whiteR, float whiteG, float whiteB, float whiteAlpha); 

	void SetAllValues(unsigned int winWidth, unsigned int winHeight, float blackR, float blackG, float blackB, float blackAlpha, float whiteR, float whiteG, float whiteB, float whiteAlpha);

	Board(Board&& other) noexcept;

	Board& operator=(Board&& other) noexcept;


	Board& operator=(const Board& other);

	inline bool GetSquareColor(size_t posX, size_t posY)
	{
		return ((posX * 8 + posY) % 2 == 0 ? true : false);
	}

	void AssignValuesForPosition();

	void SetLastPiecePressedToNull();
	
	void SeeBoard();

	void SetWindowButtonsInChessFormat(Window& window);

	void SetLastPiecePressed(unsigned int posX, unsigned int posY);
	PieceBase* GetLastPiecePressed();


	void UseSquareColor(GLuint squareColorLocation, bool whichColor);

	void UseIsTexValid(GLuint boolLocation, GLboolean condition);
	//void UseIsBlackColorBool(GLuint isBllackSquareLocation, GLboolean value);

	//std::array<std::array< Colors, 8>, 8> GetCurrentStateOfColors(); 
	//std::array<std::array< Pieces, 8>, 8> GetCurrentStateOfPieces();

	void UpdateBoard(unsigned int posX, unsigned int posY, unsigned int newPosX, unsigned int newPosY); 

	template<class T> 
	requires std::is_base_of_v<PieceBase, T>
	inline void AddPiece(std::unique_ptr<T> piece);

	PieceBase * FindPieceIn(uint32_t xCord, uint32_t yCord); 

	std::array<float, 16> GetSquareVerticies(size_t posX, size_t posY);
	std::array<unsigned int, 6> GetSquareIndicies(); 

	unsigned int GetSquareWidth() const;  
	unsigned int GetSquareHeight() const; 

	void ClearBoard(); 


	~Board();

private:

	void SetSquareVertices();


//	void SetPosition(Colors color, Pieces pieceType, unsigned int posX, unsigned int posY); 



	struct
	{
		float r;
		float g;
		float b;
		float a;
	} blackSquareColor, whiteSquareColor;
	
	PieceBase* lastPiecePressed;

	struct Piece
	{
		std::unique_ptr <PieceBase> piece;
		unsigned int posX;
		unsigned int posY;
		std::string name;
	};

	std::array<std::array<Piece, 8 >, 8 > pieces;   
	
	std::array<std::array<std::array<float, 16>, 8>, 8> squareVerticies;
	

	unsigned int squareWidth, squareHeight;

	unsigned int windowWidth, windowHeight;


	bool hasChanged;
};





template<class T>
requires std::is_base_of_v<PieceBase, T> 
inline void Board::AddPiece(std::unique_ptr<T> piece)  
{

	//int x = piece->GetPosX();
	//int y = piece->GetPosY();

	//std::cout << "the Name of the piece is: " << piece->GetName() << "\n"; 


	pieces[piece->GetPosX()][piece->GetPosY()].piece = std::move(piece);


	//std::cout << "Name of the Piece from the array is :" << pieces[x][y]->GetName() << "\n\n"; 

}