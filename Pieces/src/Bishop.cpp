#include "Bishop.h"


Bishop::Bishop() = default;


Bishop::Bishop(Colors color, bool num)
{

	pieceType = Pieces::BISHOP;
	this->color = color;

	switch (color)
	{
	case Colors::BLACK:
		SetStartingPos(Colors::BLACK, Pieces::BISHOP, num);
		break;

	case Colors::WHITE:
		SetStartingPos(Colors::WHITE, Pieces::BISHOP, num);
		break;
	}

	name = "Bishop"; 
}



Bishop::Bishop(Bishop&& other) noexcept
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


Bishop& Bishop::operator=(Bishop&& other) noexcept
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



void Bishop::FindAvailableMoves()
{
	
	MoveToDir(1, 1);
	MoveToDir(-1, 1);
	MoveToDir(1, -1);
	MoveToDir(-1, -1);

	return;
}


Bishop::~Bishop() = default; 