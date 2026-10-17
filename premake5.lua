workspace "Minecraft"
        architecture "x64"

        configurations
        {
                "Debug",
                "Release"
        }

include "AtlasLib/dependencies.lua"
include "AtlasRenderer/dependencies.lua"

include "AtlasLib/build.lua"
include "AtlasRenderer/build.lua"
include "Game/build.lua"
