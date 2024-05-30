# --------------------------------------------------------------
# data-structure library
# --------------------------------------------------------------

# headers
file(GLOB_RECURSE LAUNCHER_HEADERS *.hpp *.h)

# sources
file(GLOB_RECURSE LAUNCHER_SOURCES *.cpp)

# library
add_executable(data-structure ${LAUNCHER_SOURCES} ${LAUNCHER_HEADERS})

# intern directories
target_include_directories(data-structure PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
	$<INSTALL_INTERFACE:>/src
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(data-structure PRIVATE _DEBUG LOG_DEBUG_ENABLED)
endif()