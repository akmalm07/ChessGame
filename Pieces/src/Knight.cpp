#include "Knight.h"



Knight::Knight() = default;



Knight::Knight(Colors color, bool num)
{
	this->color = color;

	pieceType = Pieces::KNIGHT;


	switch (color)
	{
	case Colors::BLACK:
		SetStartingPos(Colors::BLACK, Pieces::KNIGHT, num);  
		break;

	case Colors::WHITE:
		SetStartingPos(Colors::WHITE, Pieces::KNIGHT, num);
		break;
	}

	name = "Knight";
}


Knight::Knight(Knight&& other) noexcept
{
	color = other.color;
	pieceType = other.pieceType;
	isAlive = other.isAlive;
	name = std::move(other.name);
	availableMoves = std::move(other.availableMoves);
	posX = other.posX;
	posY = other.posY;

	other.color = Colors::EMPTY;
	other.pieceType = Pieces::EMPTY;
	other.isAlive = false;
	other.name.clear();
	other.availableMoves.fill({ false });
	other.posX = 0;
	other.posY = 0;
}


Knight& Knight::operator=(Knight&& other) noexcept
{
	if (this != &other)
	{
		color = other.color;
		pieceType = other.pieceType;
		isAlive = other.isAlive;
		name = std::move(other.name);
		availableMoves = std::move(other.availableMoves);
		posX = other.posX;
		posY = other.posY;


		other.color = Colors::EMPTY;
		other.pieceType = Pieces::EMPTY;
		other.isAlive = false;
		other.name.clear();
		other.availableMoves.fill({ false });
		other.posX = 0;
		other.posY = 0;
	}

	return *this;
}


void Knight::CheckTheMove(int factorX, int factorY)
{
	if (!isOccupied(factorX, factorY)) 
	{
		availableMoves[posX + factorX][posY + factorY] = true; 
	}
}


void Knight::FindAvailableMoves()
{
	CheckTheMove(-1, 2);

	CheckTheMove(1, 2);
	
	CheckTheMove(2, 1);
	
	CheckTheMove(2, -1);

	CheckTheMove(1, -2);

	CheckTheMove(-1, -2);

	CheckTheMove(-2, -1);


	return;
}

bool Knight::isOccupied(int xFactor, int yFactor) 
{
	if (IsOutOfRange(xFactor, yFactor)) 
	{
		return true; 
	}

	int targetX = posX + xFactor;
	int targetY = posY + yFactor;

	if (Empty(xFactor, yFactor))
	{
		return false;
	}

	if (IsWhite(targetX, targetY) == IsWhite(posX, posY))
	{
		return true;
	}

	return false; 
}



Knight::~Knight() = default;
