#include "PieceBase.h"


unsigned int PieceBase::xPosOfKing;
unsigned int PieceBase::yPosOfKing; 

PieceBase::PieceBase()
{
	isAlive = false;

	color = Colors::EMPTY;

	pieceType = Pieces::EMPTY; 

	posX = 0;
	posY = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			availableMoves[i][j] = false; 
		}
	}

	name = "";
}



PieceBase::PieceBase(PieceBase&& other) noexcept :
	color(other.color), pieceType(other.pieceType), isAlive(other.isAlive), name(std::move(other.name)), 
	availableMoves(std::move(other.availableMoves)), posX(other.posX), posY(other.posY) 
{
	other.color = Colors::EMPTY;
	other.pieceType = Pieces::EMPTY;
	other.isAlive = false;
	other.name.clear();
	other.availableMoves.fill({ false });
	other.posX = 0;
	other.posY = 0;
}


PieceBase& PieceBase::operator=(PieceBase&& other) noexcept
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



void PieceBase::FindAvailableMoves()
{
	return;
}






//	unsigned int val = Piece::id[posX][posY];
//	Piece::id[posX][posY] = 0;
//
//	Piece::posOfPieces[xPos][yPos] = Piece::posOfPieces[posX][posY]; 
//	Piece::posOfPieces[posX][posY] = Pieces::Empty; 
//
//	std::swap(Piece::id[xPos][yPos], val);
//
//	posX = xPos; 
//	posY = yPos; 
//
//
//	return val; 


Colors PieceBase::GetColor() const 
{
	return color;
}


std::string PieceBase::GetName() const
{
	return name; 
}

Pieces PieceBase::GetPieceType()
{
	return pieceType;
}



bool PieceBase::CanTake(int xFactor, int yFactor)
{
	if (!IsOutOfRange(xFactor, yFactor) &&
		((IsWhite(posX, posY) && !IsWhite(posX + xFactor, posY + yFactor)) ||
			(!IsWhite(posX, posY) && IsWhite(posX + xFactor, posY + yFactor))))
	{
		return true;
	}
	return false;
}


bool PieceBase::IsChecking(int xFactor, int yFactor)
{
	if (!IsOutOfRange(xFactor, yFactor) && availableMoves[xPosOfKing + xFactor][yPosOfKing + yFactor])
	{
		return true;
	}
	return false;
}

bool PieceBase::IsOutOfRange(int xFactor, int yFactor)
{
	if (posX > 7 || posY > 7) 
	{
		std::cerr << "Invalid position: (" << posX << ", " << posY << ")" << std::endl;
		return true; 
	}

	if ((posX + xFactor >= 0 && posX + xFactor <= 7) &&
		(posY + yFactor >= 0 && posY + yFactor <= 7))
	{
		return false; 
	}
	return true; 
}



bool PieceBase::IsWhite(unsigned int xFactor, unsigned int yFactor)
{
	if (!IsOutOfRange(xFactor, yFactor) &&
		BoardLayout::currentStateColors[posX + xFactor][posY + yFactor] == Colors::WHITE)
	{
		return true;
	}
	return false;
}


bool PieceBase::Empty(int xFactor, int yFactor)
{
	if (!IsOutOfRange(xFactor, yFactor) &&
		BoardLayout::currentStatePieces[posX + xFactor][posY + yFactor] == Pieces::EMPTY)
	{
		return true;
	}
	return false;
}


bool PieceBase::IsFrontEmpty()
{
	if (posY >= 0 && posY < 7 && BoardLayout::currentStatePieces[posX][posY + 1] == Pieces::EMPTY)
	{
		return true;
	}
	return false;
}


void PieceBase::SetStartingPos(Colors color, Pieces pieceType, unsigned int num)
{
	// Validate the input for PAWN
	if (pieceType != Pieces::PAWN or num > 7) 
	{
		fprintf(stderr, "This function as created for only pawn pieces! (Game : Board.cpp  pawn value) ");
		return;
	}


	switch (color)
	{
	case Colors::WHITE:
		switch (pieceType)
		{
		case Pieces::PAWN:
			posY = 1;
			posX = 0 + num;
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::PAWN;
			//BoardLayout::currentStateColors[posY][posX] = Colors::WHITE; 
			break;
		}
		break;

	case Colors::BLACK:
		switch (pieceType)
		{
		case Pieces::PAWN:
			posY = 6;
			posX = 0 + num;
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::PAWN;
			//BoardLayout::currentStateColors[posY][posX] = Colors::BLACK; 
			break;
		}
		break;
	}
}


void PieceBase::SetStartingPos(Colors color, Pieces pieceType, bool num)
{


	// Validate the input for non-PAWN pieces
	if (pieceType == Pieces::PAWN)
	{
		fprintf(stderr, "This function as created for only not pawn and non royalty Pieces! (Game : Board.cpp  not pawn value) ");
		return;
	}
	switch (color)
	{
	case Colors::WHITE:
		switch (pieceType)
		{

		case Pieces::ROOK:
			posY = 0;
			posX = (num ? 0 : 7);
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::ROOK;
			//BoardLayout::currentStateColors[posY][posX] = Colors::WHITE;
			break;

		case Pieces::KNIGHT:
			posY = 0;
			posX = (num ? 1 : 6);
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::KNIGHT;
			//BoardLayout::currentStateColors[posY][posX] = Colors::WHITE;
			break;

		case Pieces::BISHOP:
			posY = 0;
			posX = (num ? 2 : 5);
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::BISHOP;
			//BoardLayout::currentStateColors[posY][posX] = Colors::WHITE;
			break;
		}
		break;

	case Colors::BLACK:
		switch (pieceType)
		{

		case Pieces::ROOK:
			posY = 7;
			posX = (num ? 0 : 7);
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::ROOK;
			//BoardLayout::currentStateColors[posY][posX] = Colors::BLACK;
			break;

		case Pieces::KNIGHT:
			posY = 7;
			posX = (num ? 1 : 6);
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::KNIGHT;
			//BoardLayout::currentStateColors[posY][posX] = Colors::BLACK;
			break;

		case Pieces::BISHOP:
			posY = 7;
			posX = (num ? 2 : 5);
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::BISHOP;
			//BoardLayout::currentStateColors[posY][posX] = Colors::BLACK;
			break;
		}
		break;
	}
}


//unsigned int PieceBase::IsCaptured(unsigned int xPos, unsigned int yPos)
//{
//	if (posX == xPos and posY == yPos)
//	{
//		return pieceID;
//	}
//	else
//	{
//		return 0;
//	}
//}

void PieceBase::SetStartingPos(Colors color, Pieces piece)
{
	if (piece != Pieces::KING and piece != Pieces::QUEEN)
	{
		fprintf(stderr, "This function was made for royalty pieces only! (PieceBase : SetStartingPos(Colors, Pieces) )");
		return;
	}
	posY = (color == Colors::BLACK) ? 7 : 0; 
	posX = (piece == Pieces::QUEEN) ? 3 : 4; 

	xPosOfKing = posX; 
	yPosOfKing = posY; 

	switch (color)
	{
	case Colors::WHITE:
		switch (piece)
		{
		case Pieces::QUEEN:
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::QUEEN;  
			//BoardLayout::currentStateColors[posY][posX] = Colors::WHITE;  
			break; 

		case Pieces::KING:
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::KING; 
			//BoardLayout::currentStateColors[posY][posX] = Colors::WHITE; 
			break;
		}
		break;

	case Colors::BLACK:
		switch (piece)
		{
		case Pieces::QUEEN:
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::QUEEN;
			//BoardLayout::currentStateColors[posY][posX] = Colors::BLACK; 
			break;

		case Pieces::KING:
			//BoardLayout::currentStatePieces[posY][posX] = Pieces::KING;
			//BoardLayout::currentStateColors[posY][posX] = Colors::BLACK; 
			break;
		}
		break;
	}
}

bool PieceBase::NoAvailableMoves()
{
	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (availableMoves[x][y]) {
				return false;
			}
		}
	}
	return true;
}

std::array<std::array<bool, 8>, 8> PieceBase::GetAvailableMoves()
{
	return availableMoves;
}

Colors PieceBase::GetColorType()
{
	return color;
}




bool PieceBase::IsAvailableMove(unsigned int posX, unsigned int posY)
{
	if (posX > 7 || posX > 7)
	{
		fprintf(stderr, "\nERROR: position out of Range ( PieceBase.cpp : IsAvailableMove(uint, uint)!!! \n");
		return false;
	}
	
	printf("Available Moves:\n");
	for (unsigned int x = 0; x < 8; ++x)
	{
		for (unsigned int y = 0; y < 8; ++y)
		{
			// Print '1' for available move, '0' otherwise
			printf("%d ", availableMoves[x][y] ? 1 : 0);
		}
		printf("\n"); // New line for each row
	}	
	
	 return availableMoves[posX][posY];
}

unsigned int PieceBase::GetPosX() const
{
	return posX;
}


unsigned int PieceBase::GetPosY() const
{
	return posY;
}


//PieceBase::Pieces PieceBase::getPiece::posOfPieces(unsigned int posX, unsigned int posY) const
//{
//	return Piece::posOfPieces[posX][posY];
//}
//
//
//void PieceBase::setPiece::posOfPieces(Pieces val, unsigned int posX, unsigned int posY)
//{
//	Piece::posOfPieces[posX][posY] = val; 
//}

void PieceBase::ClearPiece()
{
	color = Colors::EMPTY;
	pieceType = Pieces::EMPTY;
	availableMoves = { 0 };
	posX = 0;
	posY = 0;
	name = ""; 
}

PieceBase::~PieceBase()
{
	ClearPiece(); 
}

