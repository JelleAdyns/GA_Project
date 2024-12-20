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
	"Unit.cpp"	
	"Unit.h"	
	"RotatorUnit.cpp"	
	"RotatorUnit.h"	
	"DrawFloatToInt.h"
	"DrawFloatToInt.cpp"
	"GAUtils.h"
	"GAUtils.cpp"
	"structsf.h"
	"structsf.cpp"
)

add_executable(${PROJECT_NAME} WIN32  ${SOURCES} )
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES)

add_dependencies(${PROJECT_NAME} EngineLibrary)
target_link_libraries(${PROJECT_NAME} PRIVATE EngineLibrary)

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                ${CMAKE_SOURCE_DIR}/Resources
                ${CMAKE_BINARY_DIR}/Resources
)

