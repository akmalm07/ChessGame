-- Project: Game
project "Game"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
targetdir "Build/bin/%{cfg.buildcfg}/%{prj.name}"
objdir "Build/bin-int/%{cfg.buildcfg}/%{prj.name}"

files { "include/**.h", "src/**.cpp" }

includedirs {
   "include",
   "%{IncludeDir.GLFW}",
   "%{IncludeDir.GLEW}",
   "%{IncludeDir.GLM}",
   "%{IncludeDir.STBIMAGE}",
   "%{IncludeDir.GLOBAL}",
   "../Graphics/include",
   "../Pieces/include" 
}

libdirs {
   "%{LibDir.GLFWLIB}",
   "%{LibDir.GLEWLIB}",
   "%{LibDir.GRAPHICSLIB}",
   "%{LibDir.PIECESLIB}",
   
}

links {
   "Graphics",
   "Pieces",
   "glfw3",
   "glew32s", 
   "opengl32.lib"
}