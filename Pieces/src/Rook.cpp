#include "Rook.h"

Rook::Rook() = default;



Rook::Rook(Colors color, bool num) 
{


	this->color = color;

	pieceType= Pieces::ROOK;

	switch (color)
	{
	case Colors::BLACK:
		SetStartingPos(Colors::BLACK, Pieces::ROOK, num);
		break;

	case Colors::WHITE:
		SetStartingPos(Colors::WHITE, Pieces::ROOK, num);
		break;
	}

	name = "Rook";
}


Rook::Rook(Rook&& other) noexcept
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


Rook& Rook::operator=(Rook&& other) noexcept
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




void Rook::FindAvailableMoves() 
{

	MoveToDir(1, 0); 
	MoveToDir(-1, 0);
	MoveToDir(0, 1);
	MoveToDir(0, -1);

	return;
}

Rook::~Rook() = default;

