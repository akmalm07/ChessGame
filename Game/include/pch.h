#pragma once

#ifndef PCH_H_GAME
#define PCH_H_GAME
   
#ifndef GLEW_STATIC 
#define GLEW_STATIC 
#endif 




#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <stdio.h>
#include <vector> 
#include <functional>
#include <array>
#include <sstream>

#include "Definitions.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shaders.h"
#include "Texture.h"

#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


#include "BoardLayout.h"

#include "GraphicsHandlerAPI.h" 




#endif 

