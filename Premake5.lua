workspace "FroggerClone"
	architecture "x86"
	startproject "FroggerClone"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "FroggerClone"
	location "FroggerClone"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include/",
		"%{prj.name}/src/",
		"vendor/SFML/include/"
	}
	
	libdirs { "vendor/SFML/lib" }
	
	links { "opengl32.lib", "freetype.lib", "winmm.lib", "gdi32.lib", "openal32.lib", "flac.lib", "vorbisenc.lib", "vorbisfile.lib", "vorbis.lib", "ogg.lib", "ws2_32.lib" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"GAME_PLATFORM_WINDOWS",
			"SFML_STATIC" 
		}
	
	filter "configurations:Debug"
	defines "GAME_DEBUG"
    runtime "Debug"
    symbols "On"

    links 
	{ 
	"sfml-audio-s-d.lib",
	"sfml-graphics-s-d.lib",
	"sfml-network-s-d.lib",
	"sfml-system-s-d.lib",
	"sfml-window-s-d.lib" 
	}

  filter "configurations:RC"
	defines "GAME_PUBLIC"
    runtime "Release"
    optimize "On"

    links 
	{
	"sfml-audio-s.lib",
	"sfml-graphics-s.lib",
	"sfml-network-s.lib",
	"sfml-system-s.lib",
	"sfml-window-s.lib" 
	}

group "dependencies"

	--include "vendor/SFML"
