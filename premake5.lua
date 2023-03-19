workspace "Shaddock"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["GLFW"] = "Shaddock/vendor/GLFW/include"
IncludeDir["Glad"] = "Shaddock/vendor/Glad/include"
IncludeDir["ImGui"] = "Shaddock/vendor/imgui"
IncludeDir["glm"] = "Shaddock/vendor/glm"
IncludeDir["spdlog"] = "Shaddock/vendor/spdlog/include"
IncludeDir["stb_image"] = "Shaddock/vendor/stb_image"

-- Copy the GLFW premake file content to here
include "Shaddock/vendor/GLFW"
include "Shaddock/vendor/Glad"
include "Shaddock/vendor/imgui"

project "Shaddock"
	location "Shaddock"
	kind "StaticLib"
	language "C++"
	staticruntime "Off"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sdpch.h"
	pchsource "Shaddock/src/sdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
			"SD_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "SD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SD_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SD_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"Shaddock/src",
		"Shaddock/vendor"
	}

	links
	{
		"Shaddock"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SD_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SD_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SD_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SD_DIST"
		runtime "Release"
		optimize "On"

