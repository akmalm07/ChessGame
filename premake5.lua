solution "ChessGame"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Game"


--ADD SO THE FILES COULD BE INCLUDED --

-- Paths to external libraries
rootDir = "C:/Users/dev/cppdev/OpenGL/2D/ChessGame" 

IncludeDir = {}
IncludeDir["GLEW"] =    path.join(rootDir, "External/GLEW/include") 
IncludeDir["GLFW"] =    path.join(rootDir, "External/GLFW/include") 
IncludeDir["GLM"] =     path.join(rootDir, "External/GLM") 
IncludeDir["STBIMAGE"] =path.join(rootDir, "External/STBIMAGE") 
IncludeDir["GLOBAL"] =  path.join(rootDir, "global") 


LibDir = {}
LibDir["GLEWLIB"] =path.join(rootDir, "External/GLEW/lib") 
LibDir["GLFWLIB"] =path.join(rootDir, "External/GLFW/lib") 
LibDir["GRAPHICSLIB"] =path.join(rootDir, "Graphics/Build/bin/Debug/Graphics") 
LibDir["PIECESLIB"] =path.join(rootDir, "Pieces/Build/bin/Debug/Pieces") 


group "Pieces"
    include "Pieces/Pieces.lua"
    
group "Graphics"
    include "Graphics/Graphics.lua"

group "Game"
    include "Game/Game.lua"
--[[
group "Main"
    include "Main/Main.lua"
]]

    
