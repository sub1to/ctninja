local PROJECT_DIR          = path.getabsolute(".")
local PROJECT_BUILD_DIR    = path.join(PROJECT_DIR, ".build/")
local PROJECT_PROJECTS_DIR = path.join(PROJECT_DIR, ".projects/")
local PROJECT_RUNTIME_DIR  = path.join(PROJECT_DIR, ".bin/")
local PROJECT_SCRIPT_DIR   = path.join(PROJECT_DIR, "scripts/")

solution "ctninja"
	language				"C++"
	cppdialect 				"C++20" 
	configurations			{ "Debug", "Release", "Dev" }
	platforms				{ "x86", "x64" }
	
	location				(path.join(PROJECT_PROJECTS_DIR, _ACTION))
	objdir					(path.join(PROJECT_BUILD_DIR, _ACTION))
	
	filter "configurations:Debug"
		targetdir(path.join(PROJECT_RUNTIME_DIR, "debug/"))
		
	filter "configurations:Dev"
		targetdir(path.join(PROJECT_RUNTIME_DIR, "dev/"))
		
	filter "configurations:Release"
		targetdir(path.join(PROJECT_RUNTIME_DIR, "release/"))

	include "ctninja/ctninja.lua"
	include "cttest/cttest.lua"
