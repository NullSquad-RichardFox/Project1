project "Engine"
    kind "ConsoleApp"
    language "C++"    
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

    pchheader("pch.h")
    pchsource("%{wks.location}/Engine/Source/pch.cpp")

    files 
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad"
    }

    multiprocessorcompile ("on")

    filter "configurations:Debug"
        defines { "CF_DEBUG" }