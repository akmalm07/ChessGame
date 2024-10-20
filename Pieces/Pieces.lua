-- Project: Pieces
project "Pieces"
kind "StaticLib"
language "C++"
cppdialect "C++20"
targetdir "Build/bin/%{cfg.buildcfg}/%{prj.name}"
objdir "Build/bin-int/%{cfg.buildcfg}/%{prj.name}"
files { "include/**.h", "src/**.cpp" }

defines { "GLEW_STATIC" }

includedirs {
   "%{IncludeDir.GLEW}",
   "%{IncludeDir.GLOBAL}",
   "%{IncludeDir.GLM}",
   "include", 
   "src" 
   }
libdirs {"%{LibDir.GLEWLIB}"}
links { "glew32s", "opengl32.lib"}
