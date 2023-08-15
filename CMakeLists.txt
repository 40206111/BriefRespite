cmake_minimum_required(VERSION 3.20)
# Require Modern C++
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BriefRespite)

### Setup Directories ###
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Dependencies ###
add_subdirectory("SFML")
set(SFML_INCS "SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

### Assets ###
file(GLOB_RECURSE SOURCE_FILES Assets/Imgs/*.* Assets/Imgs/*.*)

### Code ###
file(GLOB_RECURSE SOURCES Code/*.cpp Code/*.h)
file(GLOB_RECURSE SOURCES Code/*.cpp Code/*.h)
add_executable(BriefRespite ${SOURCES})
target_include_directories(BriefRespite PRIVATE ${SFML_INCS})
target_link_libraries(BriefRespite sfml-graphics sfml-audio)

#set working directory to build directory
set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
	
	#####EXE STUFF#######
#Install directory within build folder, so it doesn't go into /lib or program-files
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install/")
#Installer.exe/zip built into /installer
SET(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/installer/")
#Install component for runtime dlls and stuff
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE) #stop this happening on non-release builds
INCLUDE(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION "bin/" CONFIGURATIONS Release COMPONENT SYSTEM_CMPT)
#Install component for resources
install(DIRECTORY "${CMAKE_BINARY_DIR}/Assets" DESTINATION "bin/" CONFIGURATIONS Release COMPONENT RESOURCES_CMPT)
#We disabled SFML's INSTALL component as it brings along junk, so we gotta make one ourselves
install(DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/" DESTINATION "bin" CONFIGURATIONS Release COMPONENT SFML_CMPT FILES_MATCHING PATTERN "*.dll" )
#Main Install target
install(TARGETS BriefRespite DESTINATION "bin" CONFIGURATIONS Release COMPONENT BRIEF_RESPITE_CMPT)

#Tell CPack about the libs and resources install components
set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} RESOURCES_CMPT SFML_CMPT SYSTEM_CMPT BRIEF_RESPITE_CMPT)
set(CPACK_COMPONENT_BRIEF_RESPITE_CMPT_DEPENDS RESOURCES_CMPT SFML_CMPT SYSTEM_CMPT)
set(CPACK_COMPONENT_RESOURCES_CMPT_REQUIRED TRUE)
set(CPACK_COMPONENT_SFML_CMPT_REQUIRED TRUE)
set(CPACK_COMPONENT_SYSTEM_CMPT_REQUIRED TRUE)
set(CPACK_COMPONENT_BRIEF_RESPITE_CMPT_DISPLAY_NAME "Bard Game")

IF(WIN32)
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_COMPONENT_INSTALL ON)
  set(CPACK_NSIS_HELP_LINK "https://github.com/40206111/BriefRespite")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/40206111/BriefRespite")
  set(CPACK_NSIS_CONTACT "https://github.com/40206111/")
  set(CPACK_NSIS_MUI_ICON "${CMAKE_BINARY_DIR}/Assets/imgs/icon.ico")
ELSE()
  set(CPACK_GENERATOR ZIP)
ENDIF(WIN32)

set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Brief Respite game jam game")
set(CPACK_PACKAGE_VENDOR "Emma & Ariana")

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)