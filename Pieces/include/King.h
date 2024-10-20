#pragma once

#include "PieceBase.h"


class King : public PieceBase
{
public:
	King();

	King(Colors color);

	King(King&& other) noexcept;

	King& operator= (King&& other) noexcept;

	void FindAvailableMoves() override;

	~King() override;

private:
	 
};

