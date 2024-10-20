#pragma once

#include "pch.h" 

#include "BoardLayout.h" 


class PieceBase : BoardLayout 
{
public:

	PieceBase();

	PieceBase(PieceBase&& other) noexcept;

	PieceBase& operator= (PieceBase&& other) noexcept;
	
	virtual void FindAvailableMoves();

	//unsigned int MoveToSquare(unsigned int posX, unsigned int posY);

	bool IsAvailableMove(unsigned int posX, unsigned int posY);

	bool NoAvailableMoves();
	
	std::array<std::array<bool, 8 >, 8 > GetAvailableMoves();

	Colors GetColorType();

	unsigned int GetPosX() const;
	unsigned int GetPosY() const;

	Colors GetColor() const;
	
	std::string GetName() const;

	Pieces GetPieceType(); 


	void ClearPiece(); 
	
	virtual ~PieceBase(); 

protected:

	Colors color;

	Pieces pieceType;

	bool isAlive;

	std::string name;


	static unsigned int xPosOfKing;
	static unsigned int yPosOfKing;

	std::array<std::array <bool, 8>, 8> availableMoves;

	//std::array<std::array <int, 8>, 8> idArray;

	unsigned int posX, posY;



	//PieceBase(PieceBase&& other) noexcept
	//{
	//	name = std::move(other.name);

	//}

	//PieceBase& operator=(PieceBase&& other) noexcept {
	//	if (this != &other) {
	//		name = std::move(other.name);
	//	}
	//	return *this;
	//}

protected:


	bool CanTake(int xFactor, int yFactor);
	bool IsChecking(int xFactor, int yFactor); 
	bool IsOutOfRange(int xFactor, int yFactor);
	bool IsWhite(unsigned int xFactor, unsigned int yFactor);
	bool Empty(int xFactor, int yFactor);


	bool IsFrontEmpty();

	//int PieceID(unsigned int posX, unsigned int posY);
	void SetStartingPos(Colors color, Pieces piece, unsigned int num); 
	void SetStartingPos(Colors color, Pieces piece); 
	void SetStartingPos(Colors color, Pieces pieceType, bool num);

	//unsigned int IsCaptured(unsigned int xPos, unsigned int yPos); 

};


