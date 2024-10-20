#include "King.h"


King::King() = default;


King::King(Colors color) 
{
	xPosOfKing = 0;
	yPosOfKing = 0;

	this->color = color;

	pieceType = Pieces::KING;

	switch (color)
	{
	case Colors::BLACK:
		SetStartingPos(Colors::BLACK, Pieces::KING);
		break;

	case Colors::WHITE:
		SetStartingPos(Colors::WHITE, Pieces::KING);
		break;
	}

	name = "King";
}


King::King(King&& other) noexcept
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


King& King::operator=(King&& other) noexcept
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


void King::FindAvailableMoves()
{
	if (!IsOutOfRange(1, 0) and !IsChecking(1, 0)) 
	{
		availableMoves[posX + 1][posY] = true;
	}


	if (!IsOutOfRange(0, 1) and !IsChecking(0, 1))
	{
		availableMoves[posX][posY + 1] = true;
	}


	if (!IsOutOfRange(-1, 0) and !IsChecking(-1, 0))
	{
		availableMoves[posX - 1][posY] = true;
	}


	if (!IsOutOfRange(0, -1) and !IsChecking(0, -1))
	{
		availableMoves[posX][posY - 1] = true;
	}


	if (!IsOutOfRange(1, 1) and !IsChecking(1, 1))
	{
		availableMoves[posX + 1][posY + 1] = true;
	}


	if (!IsOutOfRange(1, -1) and !IsChecking(1, -1))
	{
		availableMoves[posX + 1][posY - 1] = true;
	}


	if (!IsOutOfRange(-1, -1) and !IsChecking(-1, -1))
	{
		availableMoves[posX - 1][posY - 1] = true;
	}


	if (!IsOutOfRange(-1, 1) and !IsChecking(-1, 1))
	{
		availableMoves[posX - 1][posY + 1] = true;
	}

	return;
}

King::~King() = default;

