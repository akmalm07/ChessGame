#pragma once

#include "pch.h" 

struct BoardLayout 
{
	inline static Colors GetCurrentStateColors(unsigned int posX, unsigned int posY)
	{
		return currentStateColors[posX][posY];
	}

	inline static Pieces GetCurrentStatePieces(unsigned int posX, unsigned int posY) 
	{
		return currentStatePieces[posX][posY];
	}


	inline static void InitalizeNameOfPieces()
	{
		std::cout << "\n\n\nINIT:::";

		for (int i = 0; i < 8; i++)
		{
			std::cout << "\n";
			for (int j = 0; j < 8; j++)
			{
				std::string str = std::string(1, static_cast<char>('a' + j)) + std::to_string(i + 1);
				//std::string str((1, static_cast<char>('a' + i)) + std::to_string(j + 1));
				//std::string str((1, static_cast<char>('a' + j)) + std::to_string(i + 1));
				std::cout << " " << str;


				nameOfSquares[i][j] = str;
			}
		}
	}


	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		std::string str = (1, static_cast<char>('a' + j)) + std::to_string(i + 1);
	//		//std::string str = std::string(1, static_cast<char>('a' + j)) + std::to_string(8 - i); 
	//		nameOfSquares[i][j] = str;
	//	}
	//}

protected: 
	 
	static std::array<std::array< Colors, 8>, 8> currentStateColors; 
	static std::array<std::array< Pieces, 8>, 8> currentStatePieces; 


	static std::array<std::array< std::string, 8>, 8> nameOfSquares;
};

