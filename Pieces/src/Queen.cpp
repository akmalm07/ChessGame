#include "Queen.h"


Queen::Queen() = default;


Queen::Queen(Colors color) 
{

	this->color = color;

	pieceType = Pieces::QUEEN;

	switch (color)
	{
	case Colors::BLACK:
		SetStartingPos(Colors::BLACK, Pieces::QUEEN); 
		break;

	case Colors::WHITE:
		SetStartingPos(Colors::WHITE, Pieces::QUEEN);
		break;
	}

	name = "Queen";
}


Queen::Queen(Queen&& other) noexcept 
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


Queen& Queen::operator=(Queen&& other) noexcept
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


void Queen::FindAvailableMoves()
{
	//bishop functionality
	MoveToDir(1, 1);
	MoveToDir(-1, 1);
	MoveToDir(1, -1);
	MoveToDir(-1, -1);

	//Rook Functionality
	MoveToDir(1, 0);
	MoveToDir(-1, 0);
	MoveToDir(0, 1);
	MoveToDir(0, -1);

	return;
}


Queen::~Queen() = default;

