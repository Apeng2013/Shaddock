include "Dependencies.lua"

workspace "Shaddock"
	architecture "x86_64"
	startproject "ShaddockEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)

group "Dependencies"
	include "Shaddock/vendor/GLFW"
	include "Shaddock/vendor/Glad"
	include "Shaddock/vendor/imgui"
	include "Shaddock/vendor/yaml-cpp"
	include "Shaddock/vendor/Box2D"
group ""

include "Shaddock"

include "Sandbox"

include "ShaddockEditor"