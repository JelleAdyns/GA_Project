project(InPlaneSight)

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
	"HUD.cpp" 
	"MainMenuScreen.h"
	"MainMenuScreen.cpp"
	"PauseScreen.h"
	"PauseScreen.cpp"
	"Commands.h")

add_executable(${PROJECT_NAME} WIN32  ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES)

add_dependencies(${PROJECT_NAME} EngineLibrary)
target_link_libraries(${PROJECT_NAME} PRIVATE EngineLibrary)

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

message(STATUS "SOURCE DIR: ${CMAKE_CURRENT_BINARY_DIR}")
add_custom_target(copyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources
    ${CMAKE_CURRENT_BINARY_DIR}/Resources
    COMMENT "Copying resources into the binary folder"
)

add_dependencies(${PROJECT_NAME} copyResources)


#Filter the Units
source_group("Units" REGULAR_EXPRESSION "Unit")

#Filter FlyFish
source_group("FlyFish" REGULAR_EXPRESSION "FlyFish")

#Filter Tiles
source_group("Tiles" REGULAR_EXPRESSION "Tile")

#Filter Screens
source_group("Screens" REGULAR_EXPRESSION "Screen")