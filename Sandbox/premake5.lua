project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"
	cppdialect "C++17"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{wks.location}/Shaddock/src",
		"%{wks.location}/Shaddock/vendor"
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

