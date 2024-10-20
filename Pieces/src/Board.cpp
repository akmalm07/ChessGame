#include "pch.h"
#include "Board.h"




Board::Board() = default;
//{
//	for (size_t i = 0; i < 8; i++)
//	{
//		for (size_t j = 0; j < 8; j++)
//		{
//			pieces[i][j] = nullptr;
//			for (size_t k = 0; k < 8; k++)
//				squareVerticies[i][j][k] = { 0 };
//		}
//	}
//
//	squareWidth = 0;
//	squareHeight = 0;
//
//	windowWidth = 0;
//	windowHeight = 0;
//
//	blackSquareColor.r = 1.0f;
//	blackSquareColor.g = 1.0f;
//	blackSquareColor.b = 1.0f;
//
//	whiteSquareColor.r = 0.0f;
//	whiteSquareColor.g = 0.0f;
//	whiteSquareColor.b = 0.0f;
//
//	hasChanged = false;
//
//
//	SetSquareVertices(); 
//
//
//}

Board::Board(unsigned int winWidth, unsigned int winHeight, float blackR, float blackG, float blackB, float blackAlpha, float whiteR, float whiteG, float whiteB, float whiteAlpha)
{

	lastPiecePressed = nullptr;

	squareWidth = winWidth / 8;
	squareHeight = winHeight / 8;

	windowWidth = winWidth; 
	windowWidth = winHeight; 

	blackSquareColor.r = blackR; 
	blackSquareColor.g = blackG; 
	blackSquareColor.b = blackB;
	blackSquareColor.a = blackAlpha; 

	whiteSquareColor.r = whiteR; 
	whiteSquareColor.g = whiteG; 
	whiteSquareColor.b = whiteB; 
	whiteSquareColor.a = whiteAlpha;



	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			pieces[i][j].piece = nullptr; 
		}
	}
	
	BoardLayout::InitalizeNameOfPieces();

	SetSquareVertices();

}

void Board::SetAllValues(unsigned int winWidth, unsigned int winHeight, float blackR, float blackG, float blackB, float blackAlpha, float whiteR, float whiteG, float whiteB, float whiteAlpha)
{
	lastPiecePressed = nullptr;

	squareWidth = winWidth / 8; 
	squareHeight = winHeight / 8;

	windowWidth = winWidth;
	windowWidth = winHeight;

	blackSquareColor.r = blackR;
	blackSquareColor.g = blackG;
	blackSquareColor.b = blackB;
	blackSquareColor.a = blackAlpha;

	whiteSquareColor.r = whiteR;
	whiteSquareColor.g = whiteG;
	whiteSquareColor.b = whiteB;
	whiteSquareColor.a = whiteAlpha;


	BoardLayout::InitalizeNameOfPieces();



	SetSquareVertices();
}



Board& Board::operator=(const Board& other)
{
	if (this != &other)
	{
		lastPiecePressed = other.lastPiecePressed;

		squareWidth = other.squareWidth;
		squareHeight = other.squareHeight; 
		windowWidth = other.windowWidth; 
		windowHeight = other.windowHeight; 

		blackSquareColor = other.blackSquareColor; 
		whiteSquareColor = other.whiteSquareColor; 

		if (!other.hasChanged)
			SetSquareVertices();

		hasChanged = other.hasChanged;
	}
	return * this;
}




Board::Board(Board&& other) noexcept
	: blackSquareColor(other.blackSquareColor),
	whiteSquareColor(other.whiteSquareColor),
	pieces(std::move(other.pieces)),
	squareVerticies(std::move(other.squareVerticies)),
	squareWidth(other.squareWidth),
	squareHeight(other.squareHeight),
	windowWidth(other.windowWidth),
	windowHeight(other.windowHeight),
	hasChanged(other.hasChanged),
	lastPiecePressed(other.lastPiecePressed) 

{
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			other.pieces[i][j].piece = nullptr; 
		}
	}
}


Board& Board::operator=(Board&& other) noexcept 
{
	if (this != &other) {
		lastPiecePressed = other.lastPiecePressed;

		blackSquareColor = other.blackSquareColor;
		whiteSquareColor = other.whiteSquareColor;
		pieces = std::move(other.pieces);
		squareVerticies = std::move(other.squareVerticies);
		squareWidth = other.squareWidth;
		squareHeight = other.squareHeight;
		windowWidth = other.windowWidth;
		windowHeight = other.windowHeight;
		hasChanged = other.hasChanged;

		for (size_t i = 0; i < 8; ++i) {
			for (size_t j = 0; j < 8; ++j) {
				other.pieces[i][j].piece = nullptr; 
			}
		}
	}
	return *this;
}


void Board::SetSquareVertices()
{
	hasChanged = true;
	float xSize = 2.0f / 8.0f;
	float ySize = 2.0f / 8.0f;

	for (size_t i = 0; i < 8; i++) 
	{
		for (size_t j = 0; j < 8; j++) 
		{
			float x0 = -1.0f + j * xSize;
			float y0 = 1.0f - i * ySize;
			float x1 = x0 + xSize;
			float y1 = y0 - ySize;

			squareVerticies[i][j] = {
			//  x0,  y0,    u,    v
				x0,  y0,  0.0f, 0.0f,
				x1,  y0,  1.0f, 0.0f,
				x1,  y1,  1.0f, 1.0f,
				x0,  y1,  0.0f, 1.0f
			};
		}
	}
}


void Board::SetLastPiecePressed(unsigned int posX, unsigned int posY)
{
	if (posX > 7 || posY > 7)
	{
		fprintf(stderr, "ERROR: the positions are out of range ( Board.cpp : SetLastPiecePressed )");
		return;
	}
	lastPiecePressed = pieces[posX][posY].piece.get();   
} 


void Board::SeeBoard()
{

	printf("\n");
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			Colors color = BoardLayout::GetCurrentStateColors(i, j);

				std::string str = "";
				Pieces piece = BoardLayout::GetCurrentStatePieces(i, j);

				switch (color)
				{
				case Colors::BLACK:
					str = "b";
					break;
				case Colors::WHITE:
					str = "w";
					break;
				default:
					str = "e";
					break;
				}

				switch (piece)
				{
				case Pieces::PAWN:
					str += "Pawn";
					break;
				case Pieces::ROOK:
					str += "Rook";
					break;
				case Pieces::KNIGHT:
					str += "Knight";
					break;
				case Pieces::BISHOP:
					str += "Bishop";
					break;
				case Pieces::QUEEN:
					str += "Queen";
					break;
				case Pieces::KING:
					str += "King";
					break;
				default:
					str += "Empty";
					break;
				
			}
				std::cout << "   " << str << "   ";
		}
		std::cout << std::endl << std::endl;
	}


}

void Board::SetWindowButtonsInChessFormat(Window& window)
{
	//size_t i = 0;
	//for (auto& row : BoardLayout::nameOfSquares)
	//{
	//	size_t j = 0;
	//	std::cout << " \n";

	//	for (auto& name : row)
	//	{
	
	for (const auto& row : pieces)
	{
		for (auto& [piece, posX, posY, name] : row) 
		{


				float xCord = posX * squareWidth;
				float yCord = posY * squareHeight;  
				//std::cout << " " << column;

				std::string name;

				if (posX == 0)
					name = "a";
				else if (posX == 1)
					name = "b";
				else if (posX == 2)
					name = "c";
				else if (posX == 3)
					name = "d";
				else if (posX == 4)
					name = "e";
				else if (posX == 5)
					name = "f";
				else if (posX == 6)
					name = "g";
				else if (posX == 7)
					name = "h";


				if (posY == 0)
					name += "1";
				else if (posY == 1)
					name += "2";
				else if (posY == 2)
					name += "3";
				else if (posY == 3)
					name += "4";
				else if (posY == 4)
					name += "5";
				else if (posY == 5)
					name += "6";
				else if (posY == 6)
					name += "7";
				else if (posY == 7)
					name += "8";


				window.AddWindowButton(posX, posY, xCord, yCord, squareWidth, squareHeight,
					[this, posX, posY /*Test*/, name/*Test*/](bool whichTimeIsPressed, unsigned int posX, unsigned int posY)
					{
						int i = posX;
						int j = posY;
						std::cout << "\n\n\n NAME OF SQUARE IS " << name << "\n\n\n";


						printf("\n");

						Colors color = BoardLayout::GetCurrentStateColors(i, j);

						std::string str = "";
						Pieces piece = BoardLayout::GetCurrentStatePieces(i, j);

						switch (color)
						{
						case Colors::BLACK:
							str = "b";
							break;
						case Colors::WHITE:
							str = "w";
							break;
						default:
							str = "e";
							break;
						}

						switch (piece)
						{
						case Pieces::PAWN:
							str += "Pawn";
							break;
						case Pieces::ROOK:
							str += "Rook";
							break;
						case Pieces::KNIGHT:
							str += "Knight";
							break;
						case Pieces::BISHOP:
							str += "Bishop";
							break;
						case Pieces::QUEEN:
							str += "Queen";
							break;
						case Pieces::KING:
							str += "King";
							break;
						default:
							str += "Empty";
							break;

						}
						std::cout << "\nOn PosX: " << i << ", PosY: " << j << " is " << str << " \n"; 


						switch (whichTimeIsPressed)
						{
						case false:
						{
							printf("\n\nIS A PIECE?");

							//board.SeeBoard();



							PieceBase* piece = FindPieceIn(i, j);
							if (!piece)
							{
								SetLastPiecePressedToNull();
								return false;
							}

							piece->FindAvailableMoves();

							piece->IsAvailableMove(posX, posY);

							if (piece->NoAvailableMoves())
							{
								return false;
							}

							SetLastPiecePressed(i, j);
							printf("\n\nYES IT IS!!!  ");

							/*					std::string str;
												if (piece->GetColor() == Colors::BLACK)
													str = "black";
												else
													str = "white";

												printf("\n\IT'S A %s!!!  ", str);*/

							break;
						}
						case true:
						{
							printf("\n\nIS AN AVAILABLE MOVE?");

							PieceBase* piece = GetLastPiecePressed();
							if (!piece)
							{
								fprintf(stderr, "Piece Does not exist here!");
								return false;
							}

							if (piece->GetPosY() == posX && piece->GetPosX() == posY)
							{
								fprintf(stderr, "You Pressed the same Piece");
								return false;
							}

							if (piece->IsAvailableMove(posY, posX))
							{
								UpdateBoard(piece->GetPosX(), piece->GetPosY(), posX, posY);
							}
							else
							{
								return false;
							}
							SeeBoard();
							break;
						}
						}

						return true;

					}, name); 
			//j++;

		}
	//i++;
	}
}





void Board::AssignValuesForPosition()
{

	printf("\n\n\n BOARD LAYOUT");
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
				pieces[i][j].posX = i;  
				pieces[i][j].posY = j; 	

			if (pieces[i][j].piece)
			{
				printf(" %d ", pieces[i][j].piece->GetPieceType()); 


				BoardLayout::currentStateColors[i][j] = pieces[i][j].piece->GetColorType(); 
				BoardLayout::currentStatePieces[i][j] = pieces[i][j].piece->GetPieceType(); 
			}
			else
			{
				printf(" %d ", 0);
				BoardLayout::currentStateColors[i][j] = Colors::EMPTY;
				BoardLayout::currentStatePieces[i][j] = Pieces::EMPTY;
			}
		}
		printf("\n");
	}

}

void Board::SetLastPiecePressedToNull()
{
	lastPiecePressed = nullptr;
} 



PieceBase* Board::GetLastPiecePressed()
{
	if (lastPiecePressed)
	{
		return lastPiecePressed; 
	}
	return nullptr;
}



void Board::UseSquareColor(GLuint squareColorLocation, bool whichColor/*, GLuint squareColorWhiteLocation*/)
{

	if (!whichColor)
	{
		glUniform4f(squareColorLocation, blackSquareColor.r, blackSquareColor.g, blackSquareColor.b, blackSquareColor.a);
	}
	else
	{
		glUniform4f(squareColorLocation, whiteSquareColor.r, whiteSquareColor.g, whiteSquareColor.b, whiteSquareColor.a);
	}

	return;
}


void Board::UseIsTexValid(GLuint boolLocation, GLboolean condition)
{

	glUniform1i(boolLocation, condition);

}

//void Board::UseIsBlackColorBool(GLuint isBlackSquareLocation, GLboolean value)
//{
//	glUniform1i(isBlackSquareLocation, value); 
//}

//std::array<std::array<Colors, 8>, 8> Board::GetCurrentStateOfColors()
//{
//	return currentStateColors;
//}
//
//
//std::array<std::array<Pieces, 8>, 8> Board::GetCurrentStateOfPieces()
//{
//	return currentStatePieces; 
//}

void Board::UpdateBoard(unsigned int posX, unsigned int posY, unsigned int newPosX, unsigned int newPosY)
{
	if (newPosX > 7 || newPosY > 7 || posX > 7 || posY > 7) {
		return; 
	}

	if (pieces[newPosX][newPosY].piece && pieces[newPosX][newPosY].piece->GetPieceType() != Pieces::EMPTY)
	{
		pieces[newPosX][newPosY].piece->ClearPiece();
		BoardLayout::currentStatePieces[newPosX][newPosY] = Pieces::EMPTY;
		BoardLayout::currentStateColors[newPosX][newPosY] = Colors::EMPTY;
	}

	printf("\n\n\nBoardLayout::currentStatePieces[%d][%d] is holding %d ", posX, posY, static_cast<int>(BoardLayout::currentStatePieces[posX][posY]));
	printf("BoardLayout::currentStatePieces[%d][%d] is holding %d\n\n", posX, posY, static_cast<int>(BoardLayout::currentStatePieces[posX][posY]));


	BoardLayout::currentStatePieces[newPosX][newPosY] = BoardLayout::currentStatePieces[posX][posY];

	printf("BoardLayout::currentStatePieces[%d][%d] is holding %d", newPosX, newPosY, static_cast<int>(BoardLayout::currentStatePieces[newPosX][newPosY]));

	BoardLayout::currentStateColors[newPosX][newPosY] = BoardLayout::currentStateColors[posX][posY];

	printf("BoardLayout::currentColorPieces[%d][%d] is holding %d\n\n", newPosX, newPosY, static_cast<int>(BoardLayout::currentStateColors[newPosX][newPosY]));


	pieces[newPosX][newPosY] = std::move(pieces[posX][posY]);

	BoardLayout::currentStatePieces[posX][posY] = Pieces::EMPTY;
	BoardLayout::currentStateColors[posX][posY] = Colors::EMPTY;
	pieces[posX][posY].piece = nullptr;
}



PieceBase * Board::FindPieceIn(uint32_t xCord, uint32_t yCord)
{

	return pieces[xCord][yCord].piece.get(); 
}
   


std::array<float, 16> Board::GetSquareVerticies(size_t posX, size_t posY)
{
	if (posX > 7 || posY > 7)
		printf("Out of range! (Board.cpp : GetSquareVerticies(size_t, size_t))");

	return squareVerticies[posX][posY];   
}



std::array<unsigned int, 6> Board::GetSquareIndicies()
{
	return { 0, 1, 2, 2, 3, 0 };
}



//void Board::SetPosition(Colors color, Pieces pieceType, unsigned int posX, unsigned int posY)
//{
//	BoardLayout::currentStateColors[posX][posY] = color;
//
//	BoardLayout::currentStatePieces[posX][posY] = pieceType;
//
//}



unsigned int Board::GetSquareWidth() const
{
	return squareWidth;
}


unsigned int Board::GetSquareHeight() const
{
	return squareHeight;
}



void Board::ClearBoard()
	  {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			BoardLayout::currentStateColors[i][j] = Colors::EMPTY; 
			BoardLayout::currentStatePieces[i][j] = Pieces::EMPTY; 
			for (size_t k = 0; k < 8; k++)
				squareVerticies[i][j][k] = { 0 };  

		}
	}

	squareWidth = 0;
	squareHeight = 0;

	windowWidth = 0;
	windowHeight = 0;
	
}



Board::~Board()
{
	ClearBoard(); 


}
