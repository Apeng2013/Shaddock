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
IncludeDir["entt"] = "Shaddock/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Shaddock/vendor/yaml-cpp/include"

group "Dependencies"
	-- Copy the GLFW premake file content to here
	include "Shaddock/vendor/GLFW"
	include "Shaddock/vendor/Glad"
	include "Shaddock/vendor/imgui"
	include "Shaddock/vendor/yaml-cpp"

group ""

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
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
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

project "ShaddockEditor"
	location "ShaddockEditor"
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
		"%{IncludeDir.entt}",
		"Shaddock/src",
		"Shaddock/vendor"
	}

	links
	{
		"Shaddock"
	}

	filter "system:windows"
		systemversion "latest"

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
		"%{IncludeDir.entt}",
		"Shaddock/src",
		"Shaddock/vendor"
	}

	links
	{
		"Shaddock"
	}
	filter "system:windows"
		systemversion "latest"

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

