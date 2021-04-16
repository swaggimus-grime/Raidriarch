workspace "Raidriarch"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Raidriarch"
	location "Raidriarch"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "raidpch.h"
	pchsource "Raidriarch/src/raidpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RAID_PLATFORM_WINDOWS",
			"RAID_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

	filter "configurations:Debug"
		defines "RAID_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RAID_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RAID_DIST"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Raidriarch/vendor/spdlog/include",
		"Raidriarch/src"
	}

	links
	{
		"Raidriarch"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RAID_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RAID_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RAID_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RAID_DIST"
		optimize "On"