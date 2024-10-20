#pragma once

#include "PieceBase.h"

#include "pch.h"


class Pawn : public PieceBase, public BoardLayout
{
public:
	Pawn();

	Pawn(Pawn&& other) noexcept;

	Pawn& operator= (Pawn&& other) noexcept;

	Pawn(Colors color, unsigned int num);
	 
	void FindAvailableMoves() override;  

	~Pawn();

private:

	bool firstMove; 

};

