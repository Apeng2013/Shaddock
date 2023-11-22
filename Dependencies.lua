

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Shaddock/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Shaddock/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Shaddock/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Shaddock/vendor/glm"
IncludeDir["spdlog"] = "%{wks.location}/Shaddock/vendor/spdlog/include"
IncludeDir["stb_image"] = "%{wks.location}/Shaddock/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Shaddock/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Shaddock/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Shaddock/vendor/ImGuizmo"
IncludeDir["Box2D"] = "%{wks.location}/Shaddock/vendor/Box2D/include"
IncludeDir["mono"] = "%{wks.location}/Shaddock/vendor/mono/include"

LibraryDir = {}
LibraryDir["mono"] = "%{wks.location}/Shaddock/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"