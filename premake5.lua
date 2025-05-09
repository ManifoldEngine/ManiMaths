workspace "ManiMaths"
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    configurations { "Debug" }
    startproject "Sandbox"
    architecture "x64"
    language "C++"
    cppdialect "C++20"
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)
    symbols "On"

    includedirs { "include/" }
    includedirs { "ThirdParties/ManiTests/include" }
    includedirs { "ThirdParties/ManiZ/include" }

project "Sandbox"
    kind "ConsoleApp"
    location "%{prj.name}"

    files { "%{prj.name}/**.h", "%{prj.name}/**.cpp" }
