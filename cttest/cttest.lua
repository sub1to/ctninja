project "cttest"
	uuid				"2139e4a9-12b3-4a47-aa38-543f9fae7a19"
	kind				"ConsoleApp"
	characterset		"MBCS"
	targetname 			"cttest"
	language			"C++"
	cppdialect 			"C++20" 
	
	--pchheader 			"src/pch.h"
	--pchsource 			"src/pch.cpp"
	

	files
	{
		"src/**.asm",
		"src/**.cpp",
		"src/**.c",
		"src/**.hpp",
		"src/**.h",
		"src/**.rc",
	}
	
	excludes {
		
	}
	
	vpaths {
		["src/*"]	= { "cttest", "src" },
		["externals/*"]	= { "externals" },
	}
	
	includedirs {
		"include/",

		"../ctninja/include",
	}
	
	libdirs {
		
	}
	
	linkoptions {
		--"/MANIFESTUAC:\"level='requireAdministrator'\""
	}
	
	
	links {
		"ctninja"
	}
	
	defines {
		
	}

	filter "platforms:x64"
		targetname "cttest64"

	filter "platforms:x86"
		targetname "cttest32"

	
	filter "configurations:Debug"
		defines { "DEBUG" }
		optimize "Off"
		symbols "On"
		
	filter "configurations:Dev"
		flags { "LinkTimeOptimization", "NoIncrementalLink" }
		optimize "Off"
		
	filter "configurations:Release"
		flags { "LinkTimeOptimization", "NoIncrementalLink" }
		defines { "NDEBUG" }
		optimize "Full"
		symbols "Off"