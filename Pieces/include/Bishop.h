#pragma once

#include "CommonDirections.h"


class Bishop : public CommonDirections
{
public:
	Bishop();

	Bishop(Bishop&& other) noexcept;

	Bishop& operator= (Bishop&& other) noexcept;

	Bishop(Colors color, bool num);

	void FindAvailableMoves() override;

	~Bishop() override;
};

