workspace "Project1"
    architecture "x64"
    startproject "Engine"

    configurations 
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}/%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Engine/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Engine/ThirdParty/Glad/include"
IncludeDir["glm"] = "%{wks.location}/Engine/ThirdParty/glm/include"
IncludeDir["stb_image"] = "%{wks.location}/Engine/ThirdParty/stb_image/include"

group "Dependencies"
    include "Engine/ThirdParty/GLFW/GLFW.lua"
    include "Engine/ThirdParty/Glad/Glad.lua"
group ""

group "Project"
    include "Engine/Engine.lua"
group ""