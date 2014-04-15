newoption{
	trigger = "destination", 
	description = "Destination folder"
}

-- Root directory of project checkout relative to this .lua file
ROOT_DIR = "../"

-- System libraries directory
SYSTEM_LIBS = "D:/libs"

-- Boost libraries directory
BOOST_LIBS = "d:/Sources/boost_1_55_0/"

-- Google Test libraries
-- https://code.google.com/p/googletest/wiki/V1_7_Primer
GTEST_LIBS = ""

wx_lib_files = {
	"wxmsw31ud_core",
	"wxbase31ud",
	"wxtiffd",
	"wxjpegd",
	"wxpngd",
	"wxzlibd",
	"wxregexud",
	"wxexpatd"
}

ms_lib_files = {
	-- "kernel32"
	-- "user32"
	"gdi32",
	-- "comdlg32"
	-- "winspool"
	-- "winmm"
	-- "shell32"
	"comctl32",
	-- "ole32"
	-- "oleaut32"
	"uuid",
	"rpcrt4"
	-- "advapi32"
	-- "wsock32"
	-- "wininet"
}

project_libs = table.join(wx_lib_files, ms_lib_files)

-- Create the solution and make it active
solution "wxstyle"
	configurations{ "Debug", "Release" }
	location( _OPTIONS["destination"] )

	defines {"_CRT_SECURE_NO_WARNINGS"}

	-- Create the library project
	project "wxStyle"
		language "C++"
		kind "StaticLib"
		targetdir (ROOT_DIR.."/lib")

		files {
			ROOT_DIR.."/include/**.h",
			ROOT_DIR.."/src/**.cpp"
		}
		
		includedirs {
			ROOT_DIR.."/include",
			SYSTEM_LIBS.."/include",
			BOOST_LIBS
		}
		
		libdirs {
		    SYSTEM_LIBS.."/lib"
		}
		
		links(project_libs)

		configuration "Debug"
			defines { "DEBUG" }
			targetname "wxstyle_d"

			-- enable debug information
			flags {"Symbols"}

		configuration "Release"
			defines { "NDEBUG" }
			targetname "wxstyle"
		
	-- create the demo project
	project "demo"
		language "C++"
		kind "WindowedApp"
		targetdir (ROOT_DIR.."/binaries")

		files {
			ROOT_DIR.."/demo/**.h",
			ROOT_DIR.."/demo/**.cpp",
		}
		
		includedirs {
			ROOT_DIR.."/include",
			SYSTEM_LIBS.."/include",
			BOOST_LIBS
		}
		
		libdirs {
		    SYSTEM_LIBS.."/lib",
		    ROOT_DIR.."/lib"
		}
		
		links(table.join(project_libs, {"wxStyle"}))

		flags {"WinMain"}

		configuration "Debug"
			defines { "DEBUG", "wxUSE_GUI" }
			targetname "demo_d"

			-- enable debug information
			flags {"Symbols"}

		configuration "Release"
			defines { "NDEBUG", "wxUSE_GUI" }
			targetname "demo"

	-- Create the test project
	project "tests"
		language "C++"
		kind "ConsoleApp"
		targetdir (ROOT_DIR.."/binaries")

		files {
			ROOT_DIR.."/tests/**.h",
			ROOT_DIR.."/tests/**.cpp",
		}
		
		includedirs {
			ROOT_DIR.."/include",
			SYSTEM_LIBS.."/include",
			BOOST_LIBS
		}
		
		libdirs {
		    SYSTEM_LIBS.."/lib",
		    ROOT_DIR.."/lib",
		    BOOST_LIBS.."stage/lib"
		}
		
		links(table.join(project_libs, {"wxStyle"}))

		configuration "Debug"
			defines { "DEBUG", "wxUSE_GUI" }
			targetname "tests_d"

			-- enable debug information
			flags {"Symbols"}

		configuration "Release"
			defines { "NDEBUG", "wxUSE_GUI" }
			targetname "tests"
