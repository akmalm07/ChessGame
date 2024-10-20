#pragma once

#include "PieceBase.h"


class Knight : public PieceBase
{
public:
	Knight();

	Knight(Colors color, bool num);

	Knight(Knight&& other) noexcept;

	Knight& operator= (Knight&& other) noexcept;

	void FindAvailableMoves() override;

	~Knight() override;
private:

	void CheckTheMove(int factorX, int factorY);
	bool isOccupied(int xFactor, int yFactor);

};

