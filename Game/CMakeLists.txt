project(GameName)

set(GUI_TYPE WIN32)

set(SOURCES 
	"Main.cpp"
	"Game.cpp"
	"Game.h"	
	"Cannon.cpp"	
	"Cannon.h"	
	"FlyFish.cpp"	
	"FlyFish.h"	
	"Level.cpp"	
	"Level.h"	
	"Player.cpp"	
	"Player.h"	
	"Projectile.cpp"	
	"Projectile.h"	
	"Unit.h"	
	"RotatorUnit.cpp"	
	"RotatorUnit.h"	
	"DrawFloatToInt.h"
	"DrawFloatToInt.cpp"
	"GAUtils.h"
	"GAUtils.cpp"
	"structsf.h"
	"structsf.cpp"
	"TeleportUnit.h"
	"TeleportUnit.cpp"
	"BoosterUnit.h"
	"BoosterUnit.cpp"
	"Box.h"
	"Box.cpp" 
	"BlackHoleTile.h" "BlackHoleTile.cpp" "Tile.h" "Tile.cpp")

add_executable(${PROJECT_NAME} WIN32  ${SOURCES} )
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES)

add_dependencies(${PROJECT_NAME} EngineLibrary)
target_link_libraries(${PROJECT_NAME} PRIVATE EngineLibrary)

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

message(STATUS "SOURCE DIR: ${CMAKE_CURRENT_BINARY_DIR}")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                ${CMAKE_SOURCE_DIR}/Resources
                ${CMAKE_CURRENT_BINARY_DIR}/Resources
)

#find_library(VLD vld
#    HINTS "C:/Program Files (x86)/Visual Leak Detector/lib/Win32" "C:/Program Files/Visual Leak Detector/lib/Win64")
#  find_file(VLD_H vld.h
#    HINTS "C:/Program Files (x86)/Visual Leak Detector/include" "C:/Program Files/Visual Leak Detector/include")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FIwinsock2.h")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \"/FI${VLD_H}\"")
#  get_filename_component(VLD_LIBRARY_DIR "${VLD}" PATH)
#  link_directories("${VLD_LIBRARY_DIR}")
#find_library(VLD vld HINTS "C:\\Program Files (x86)\\Visual Leak Detector\\lib\\Win64")
#find_path(VLD_H vld.h HINTS "C:\\Program Files (x86)\\Visual Leak Detector\\include")
#include_directories(${VLD_H})
#link_libraries(${VLD})

#Filter the Units
source_group("Units" REGULAR_EXPRESSION "Unit")

#Filter FlyFish
source_group("FlyFish" REGULAR_EXPRESSION "FlyFish")

#Filter Tiles
source_group("Tiles" REGULAR_EXPRESSION "Tile")