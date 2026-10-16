project "Game"
        kind "ConsoleApp"
        language "C++"
        
	targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
        
        files
        {
                "source/**.h",
                "source/**.hpp",
                "source/**.cpp",
        }

        includedirs
        {
                "%{IncludeDir.AtlasLib}",
                "%{IncludeDir.AtlasRenderer}",
                "%{IncludeDir.glm}",
                "%{IncludeDir.Glad}",
                "%{IncludeDir.spdlog}",
                "%{IncludeDir.imgui}"
        }

        links
        {
                "AtlasLib",
                "AtlasRenderer"
        }

        filter "system:windows"
                cppdialect "C++latest"
                staticruntime "off"
                systemversion "latest"

                defines 
                {
                    "AT_PLATFORM_WINDOWS",
                }

        filter "configurations:Debug"
                defines "AT_DEBUG"
                symbols "on"
                runtime "Debug"

        filter "configurations:Release"
                defines "AT_RELEASE"
                optimize "on"
                runtime "Release"