#include "CommonDirections.h"


void CommonDirections::MoveToDir(int dirX, int dirY)
{
	int i = 1;
	while (!IsOutOfRange(i * dirX, i * dirY))
	{
		int newX = posX + i * dirX;
		int newY = posY + i * dirY;

		if (Empty(i * dirX, i * dirY))
		{
			availableMoves[newX][newY] = true;
		}
		else if (CanTake(i * dirX, i * dirY))
		{
			availableMoves[newX][newY] = true;
			break;
		}

		if (IsChecking(i * dirX, i * dirY))
		{
			availableMoves[newX][newY] = false;
		}
		i++;
	}
}
