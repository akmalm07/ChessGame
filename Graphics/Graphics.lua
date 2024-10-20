-- Project: Graphics
project "Graphics"
kind "StaticLib"
language "C++"
cppdialect "C++20"
targetdir "Build/bin/%{cfg.buildcfg}/%{prj.name}"
objdir "Build/bin-int/%{cfg.buildcfg}/%{prj.name}"
files { "include/**.h", "src/**.cpp" }

defines { "GLEW_STATIC" }

includedirs {
   "%{IncludeDir.GLFW}",
   "%{IncludeDir.GLEW}",
   "%{IncludeDir.GLM}",
   "%{IncludeDir.STBIMAGE}",
   "%{IncludeDir.GLOBAL}",
   "include", 
   "src" 
   }
libdirs {
   "%{LibDir.GLEWLIB}",
   "%{LibDir.GLFWLIB}"
      }
links { "glew32s", "glfw3", "opengl32.lib" }
