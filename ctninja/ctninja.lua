project "ctninja"
	uuid				"acc21cf6-e398-4850-93a0-f4d6305ef451"
	kind				"StaticLib"
	characterset		"Unicode"
	language			"C++"
	cppdialect 			"C++20" 

	pchheader 			"pch.h"
	pchsource 			"src/pch.cpp"

	files
	{
		"include/ctninja/**.h",
		"include/ctninja/**.hpp",

		"src/**.inc",
		"src/**.asm",
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c",
		"src/**.h",
	}
	
	vpaths {
		["include"]		= { "include/ctninja/**" },
		["src"]			= { "src/**" },
	}
	
	includedirs {
		"include/ctninja",
	}
	
	libdirs {
		
	}
	
	links {
		
	}

	filter "platforms:x64"
		targetname "ctninja64"

	filter "platforms:x86"
		targetname "ctninja32"
		excludes {
			"src/teb64.asm"
		}

		
	filter "configurations:Debug"
		defines { "DEBUG" }
		optimize "Off"
		symbols "On"
		linktimeoptimization "Off"
		
	filter "configurations:Dev"
		flags { "NoIncrementalLink" }
		optimize "Off"
		symbols "Off"
		linktimeoptimization "On"
		
	filter "configurations:Release"
		flags { "NoIncrementalLink" }
		defines { "NDEBUG" }
		optimize "Full"
		symbols "Off"
		linktimeoptimization "On"
		rtti "Off"
		
