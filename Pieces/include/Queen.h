#pragma once

#include "CommonDirections.h"


class Queen : public CommonDirections
{
public:
	Queen(); 

	Queen(Colors color);

	Queen(Queen&& other) noexcept;

	Queen& operator= (Queen&& other) noexcept;

	void FindAvailableMoves() override;

	~Queen() override;
};

