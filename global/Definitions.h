#ifndef DEFINITIONS
#define DEFINITIONS


enum class MouseButton
{
	LEFT = 0,
	RIGHT = 1
};

enum class Turn
{
	FIRST = 0,
	SECOND = 1 
};


enum class Pieces
{
	EMPTY = 0,
	PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum class Colors
{
	EMPTY = 0,
	WHITE,
	BLACK
};



enum class Mods
{
	EMPTY = 0,
	CONTROL,
	SHIFT,
	ALT,
	SUPER
};



#endif