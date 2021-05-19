workspace "Raidriarch"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Raidriarch/vendor/GLFW/include"
IncludeDir["Glad"] = "Raidriarch/vendor/Glad/include"
IncludeDir["ImGui"] = "Raidriarch/vendor/imgui"
IncludeDir["glm"] = "Raidriarch/vendor/glm"

group "Dependencies"
	include "Raidriarch/vendor/GLFW"
	include "Raidriarch/vendor/Glad"
	include "Raidriarch/vendor/imgui"
group ""

project "Raidriarch"
	location "Raidriarch"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "raidpch.h"
	pchsource "Raidriarch/src/raidpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RAID_PLATFORM_WINDOWS",
			"RAID_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RAID_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RAID_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RAID_DIST"
		runtime "Release"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Raidriarch/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Raidriarch"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RAID_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RAID_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RAID_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RAID_DIST"
		runtime "Release"
		optimize "on"
		