cmake_minimum_required(VERSION 3.20)

project(BriefRespite VERSION 0.1)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(GameConfig.h.in GameConfig.h)

SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Dependencies ###
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# Define sources and executable
file(GLOB_RECURSE SOURCES Code/*.cpp Code/*.h)
add_executable(BriefRespite ${SOURCES})
target_include_directories(BriefRespite PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(BriefRespite PRIVATE ${SFML_INCS})
target_link_libraries(BriefRespite sfml-graphics sfml-audio)

#set working directory to build directory
set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))