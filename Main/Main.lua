-- Project: Main
project "Main"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
targetdir "Build/bin/%{cfg.buildcfg}/%{prj.name}"
objdir "Build/bin-int/%{cfg.buildcfg}/%{prj.name}"
files { "include/**.h", "src/**.cpp" }
includedirs { 
   "../Graphics",
   "../Pieces",
   "%{IncludeDir.GLFW}",
   "%{IncludeDir.GLEW}",
   "%{IncludeDir.GLM}",
   "%{IncludeDir.STBIMAGE}",
   "%{IncludeDir.GLOBAL}",
   "../Game",
   "include", 
   "src"
}
libdirs { "%{LibDir.GLEWLIB}", "%{LibDir.GLFWLIB}" } 
links { "Game",  "glew32s", "Graphics", "Pieces" }

