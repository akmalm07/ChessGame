
#pragma once

#include "CommonDirections.h"

class Rook : public CommonDirections
{
public:
	Rook();

	Rook(Colors color, bool num);
	
	Rook(Rook&& other) noexcept;

	Rook& operator= (Rook&& other) noexcept;

	void FindAvailableMoves() override;

	~Rook() override; 

};

