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
		message(STATUS "SHAREDLIB -- Default to Release build.")
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Build Type" FORCE)
	endif()
	message(STATUS "SHAREDLIB -- Build type set to: ${CMAKE_BUILD_TYPE}")
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose Build Type")

	# Set the valid options for cmake-gui drop-down list. CMake SHAREDLIB for vscode does not (but should) respect this.
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

project(SHAREDLIB VERSION "1.0.0" LANGUAGES C CXX)

# Find Git module.
find_package(Git)
if (Git_FOUND)
	message(STATUS "SHAREDLIB -- Git found: ${GIT_EXECUTABLE}")
endif()

# Grab the Tacent library from github at configure time.
include(FetchContent)
FetchContent_Declare(
	tacent
	GIT_REPOSITORY https://github.com/bluescan/tacent.git
)
FetchContent_MakeAvailable(tacent)

# Add the actual library and programs that use the library
add_subdirectory(mylib)
add_subdirectory(useslib)
