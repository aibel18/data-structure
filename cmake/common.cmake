message(STATUS "Project name: ${PROJECT_NAME}")

if(BUILD_SHARED_LIBS)
	message(STATUS "Library Type: Dynamic library")
else()
	message(STATUS "Library Type: Static library")
endif()

# config directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}${OUT_BUILD}/lib" CACHE PATH "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}${OUT_BUILD}/lib" CACHE PATH "" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}${OUT_BUILD}/bin" CACHE PATH "" FORCE)

# Directory output files for multi config generators
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_SOURCE_DIR}${OUT_BUILD}/bin" CACHE PATH "" FORCE)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_SOURCE_DIR}${OUT_BUILD}/lib" CACHE PATH "" FORCE)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_SOURCE_DIR}${OUT_BUILD}/lib" CACHE PATH "" FORCE)
endforeach()

set(VT_PROJECT_PATH ${CMAKE_SOURCE_DIR})
set(VT_SOURCE_PATH ${CMAKE_SOURCE_DIR}/src)
set(VT_EXTERN_PATH ${CMAKE_SOURCE_DIR}/extern)
set(VT_ASSETS_PATH ${CMAKE_SOURCE_DIR}/assets)
set(VT_GITEXTERN_INSTALL_PATH ${CMAKE_BINARY_DIR}/gitextern)

# config build
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd")
set(CMAKE_MINSIZEREL_POSTFIX "_ms")

if(WIN32)
	set(CMAKE_USE_RELATIVE_PATHS "1")

	# Set compiler flags for "release"
	set(CMAKE_CXX_FLAGS_RELEASE "/MD /MP /Ox /Ob2 /Oi /Ot /fp:fast /D NDEBUG /openmp")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /MP /Ox /Ob2 /Oi /Ot /fp:fast /D NDEBUG /openmp")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP /openmp")
endif(WIN32)

if(UNIX)
	set(CMAKE_USE_RELATIVE_PATHS "1")

	# Set compiler flags for "release"
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -fopenmp")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -DNDEBUG -march=native -fopenmp")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fopenmp")
endif(UNIX)

if(APPLE)
	set(CMAKE_MACOSX_RPATH 1)
endif(APPLE)

add_definitions(-D_CRT_SECURE_NO_DEPRECATE)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(EXT_CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# use double precision
if(USE_DOUBLE_PRECISION)
	message(STATUS "Real = double")
	add_definitions(-DUSE_DOUBLE)
else()
	message(STATUS "Real = float")
endif(USE_DOUBLE_PRECISION)

# use cuda
if(USE_CUDA)
	# find nvcc
	include(cuda)

	if(HAVE_LLVM)
		# add_subdirectory(cuda-c-linking) # modify
	endif(HAVE_LLVM)

	# library for cuda
	add_subdirectory(src/Cu) # modify
endif(USE_CUDA)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# c++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)