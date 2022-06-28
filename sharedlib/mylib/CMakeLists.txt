cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)

# Set default build-type (AKA the configuration in other IDEs).
set(CMAKE_BUILD_TYPE_INIT Release)

# Setup Release and Debug build-types (only).
# No reason to set CMAKE_CONFIGURATION_TYPES if it's not a multiconfig generator
# Also no reason mess with CMAKE_BUILD_TYPE if it's a multiconfig generator.
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (isMultiConfig)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
else()
	if (NOT DEFINED CMAKE_BUILD_TYPE)
		message(STATUS "library -- Default to Release build.")
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Build Type" FORCE)
	endif()
	message(STATUS "libraryLIBRARY -- Build type set to: ${CMAKE_BUILD_TYPE}")
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose Build Type")

	# Set the valid options for cmake-gui drop-down list. CMake tools for vscode does not (but should) respect this.
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# This include specifies the project and version.
include("src/version.cmake.h")
project(mylib VERSION "${MYLIB_VERSION}" LANGUAGES C CXX)
message(STATUS "${PROJECT_NAME} version ${PROJECT_VERSION}")

# Files needed to create executable.
add_library(
	${PROJECT_NAME}
	src/version.cpp
	src/mylib.cpp
)

# Include directories needed to build.
target_include_directories(
	"${PROJECT_NAME}"
	# Export the include path for users of this library
    PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
	# Add the include path for the library to search as it is, itself, built
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE
		ARCHITECTURE_X64
		$<$<CONFIG:Debug>:CONFIG_DEBUG>
		$<$<CONFIG:Release>:CONFIG_RELEASE>
		$<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_DEPRECATE>
		$<$<PLATFORM_ID:Windows>:PLATFORM_WINDOWS>
		$<$<PLATFORM_ID:Linux>:PLATFORM_LINUX>
)

# Set compiler option flags based on specific compiler and configuration.
target_compile_options(
	${PROJECT_NAME}
	PRIVATE
		# MSVC compiler.
		$<$<CXX_COMPILER_ID:MSVC>:/W2 /GS /Gy /Zc:wchar_t /Gm- /Zc:inline /fp:precise /WX- /Zc:forScope /Gd /FC>

		# Clang compiler.
		$<$<CXX_COMPILER_ID:Clang>:-Wno-switch>

		# GNU compiler.
		$<$<CXX_COMPILER_ID:GNU>:-Wno-unused-result>
		$<$<CXX_COMPILER_ID:GNU>:-Wno-multichar>

		# Clang and GNU.
		$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wno-format-security>

		$<$<AND:$<CONFIG:Debug>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O0>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Od>
		$<$<AND:$<CONFIG:Release>,$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>>:-O2>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# This is how you set things like CMAKE_DEBUG_POSTFIX for a target.
set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	# DEBUG_POSTFIX "d"												# Add a 'd' before the extension for debug builds.
	MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"	# Use multithreaded or multithreaded-debug runtime on windows.
	# More prop-value pairs here.
)

# Dependencies.
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		Foundation Math System Image
		$<$<PLATFORM_ID:Windows>:shlwapi.lib>
		$<$<PLATFORM_ID:Windows>:Dbghelp.lib>

		$<$<PLATFORM_ID:Linux>:m>
		$<$<PLATFORM_ID:Linux>:stdc++>
		$<$<PLATFORM_ID:Linux>:dl>
)

if (MSVC)
	# target_link_options(${PROJECT_NAME} PRIVATE "/ENTRY:mainCRTStartup")
	# target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
	if (CMAKE_BUILD_TYPE MATCHES Debug)
		target_link_options(${PROJECT_NAME} PRIVATE "/NODEFAULTLIB:LIBCMT.lib")
	endif()
endif()
