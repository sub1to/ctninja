project "ctninja"
	uuid				"acc21cf6-e398-4850-93a0-f4d6305ef451"
	kind				"StaticLib"
	characterset		"MBCS"
	language			"C++"
	cppdialect 			"C++20" 

	pchheader 			"pch.h"
	pchsource 			"src/pch.cpp"

	files
	{
		"include/**.h",
		"include/**.hpp",

		"src/**.inc",
		"src/**.asm",
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c",
		"src/**.h",
	}
	
	vpaths {
		["include/*"]		= { "ctninja", "include" },
		["src/*"]			= { "ctninja", "src" },
	}
	
	includedirs {
		"include/",
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
		
	filter "configurations:Dev"
		flags { "LinkTimeOptimization", "NoIncrementalLink" }
		optimize "Off"
		symbols "Off"
		
	filter "configurations:Release"
		flags { "LinkTimeOptimization", "NoIncrementalLink" }
		defines { "NDEBUG" }
		optimize "Full"
		symbols "Off"
		
