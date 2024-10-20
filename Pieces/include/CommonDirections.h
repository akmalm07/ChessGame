#pragma once
#include "PieceBase.h"


class CommonDirections : public PieceBase
{
protected:
	void MoveToDir(int posX, int posY);
};

