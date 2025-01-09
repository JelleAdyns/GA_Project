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
	"LevelScreen.cpp"	
	"LevelScreen.h"	
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
	"BlackHoleTile.h"
	"BlackHoleTile.cpp"
	"Tile.h"
	"Tile.cpp" 
	"ProjectileOverlapHandler.h" 
	"ProjectileOverlapHandler.cpp"
	"FenceTile.h" 
	"FenceTile.cpp"
	"PhaserUnit.h"
	"PhaserUnit.cpp"
	"Screen.h"
	"Target.h" 
	"Target.cpp"
	"HUD.h"
	"HUD.cpp")

add_executable(${PROJECT_NAME} WIN32  ${SOURCES})
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

#Filter the Units
source_group("Units" REGULAR_EXPRESSION "Unit")

#Filter FlyFish
source_group("FlyFish" REGULAR_EXPRESSION "FlyFish")

#Filter Tiles
source_group("Tiles" REGULAR_EXPRESSION "Tile")

#Filter Screens
source_group("Screens" REGULAR_EXPRESSION "Screen")