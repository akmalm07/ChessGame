#include "Pawn.h"


Pawn::Pawn() : PieceBase()
{
	firstMove = false;
}


Pawn::Pawn(Colors color, unsigned int num) : PieceBase() 
{
	firstMove = true;

	this->color = color; 
	
	pieceType = Pieces::PAWN;
	
	name = "Pawn";

	switch (color)
	{ 
		case Colors::WHITE:
			SetStartingPos(Colors::WHITE, Pieces::PAWN, num);   
			break;
		case Colors::BLACK:
			SetStartingPos(Colors::BLACK, Pieces::PAWN, num);  
			break;
	} 

	firstMove = true;

}



Pawn::Pawn(Pawn&& other) noexcept
{
	color = other.color;
	pieceType = other.pieceType;
	isAlive = other.isAlive;
	name = std::move(other.name);
	availableMoves = std::move(other.availableMoves);
	posX = other.posX;
	posY = other.posY;
	firstMove = other.firstMove;

	other.color = Colors::EMPTY;
	other.pieceType = Pieces::EMPTY;
	other.isAlive = false;
	other.name.clear();
	other.availableMoves.fill({ false });
	other.posX = 0;
	other.posY = 0;
	other.firstMove = 0;
}


Pawn& Pawn::operator=(Pawn&& other) noexcept
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

void Pawn::FindAvailableMoves()
{
    std::cout << "Pawn: PosX: " << posX << "  PosY: " << posY << "\n\n";

    // Reset availableMoves for this call
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            availableMoves[i][j] = false;  // Ensure the available moves are reset
        }
    }

    // Move forward
    if (!IsWhite(posX, posY))  // Assuming the function returns true if the piece is white
    {
        // Move one step forward
        if (!IsOutOfRange(posX, posY + 1) && Empty(posX, posY + 1))
        {
            availableMoves[posX][posY + 1] = true;
            std::cout << "Move one step forward to (" << posX << ", " << posY + 1 << ")\n";
            // Move two steps forward if it's the first move
            if (firstMove && Empty(posX, posY + 2))
            {
                availableMoves[posX][posY + 2] = true;
                std::cout << "Move two steps forward to (" << posX << ", " << posY + 2 << ")\n";
            }
        }

        // Capture diagonally to the right
        if (!IsOutOfRange(posX + 1, posY + 1) && !Empty(posX + 1, posY + 1) && CanTake(posX + 1, posY + 1))
        {
            availableMoves[posX + 1][posY + 1] = true;
            std::cout << "Capture to the right at (" << posX + 1 << ", " << posY + 1 << ")\n";
        }

        // Capture diagonally to the left
        if (!IsOutOfRange(posX - 1, posY + 1) && !Empty(posX - 1, posY + 1) && CanTake(posX - 1, posY + 1))
        {
            availableMoves[posX - 1][posY + 1] = true;
            std::cout << "Capture to the left at (" << posX - 1 << ", " << posY + 1 << ")\n";
        }
    }
    else
    {
        // Move one step forward
        if (!IsOutOfRange(posX, posY - 1) && Empty(posX, posY - 1))
        {
            availableMoves[posX][posY - 1] = true;
            std::cout << "Move one step forward to (" << posX << ", " << posY - 1 << ")\n";
            // Move two steps forward if it's the first move
            if (firstMove && Empty(posX, posY - 2))
            {
                availableMoves[posX][posY - 2] = true;
                std::cout << "Move two steps forward to (" << posX << ", " << posY - 2 << ")\n";
            }
        }

        // Capture diagonally to the right
        if (!IsOutOfRange(posX + 1, posY - 1) && !Empty(posX + 1, posY - 1) && CanTake(posX + 1, posY - 1))
        {
            availableMoves[posX + 1][posY - 1] = true;
            std::cout << "Capture to the right at (" << posX + 1 << ", " << posY - 1 << ")\n";
        }

        // Capture diagonally to the left
        if (!IsOutOfRange(posX - 1, posY - 1) && !Empty(posX - 1, posY - 1) && CanTake(posX - 1, posY - 1))
        {
            availableMoves[posX - 1][posY - 1] = true;
            std::cout << "Capture to the left at (" << posX - 1 << ", " << posY - 1 << ")\n";
        }
    }

    // Print the available moves array for debugging
    std::cout << "Available Moves:\n";
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            std::cout << availableMoves[i][j] << " ";
        }
        std::cout << "\n";
    }
}



Pawn::~Pawn()
{
	firstMove = false;  
}