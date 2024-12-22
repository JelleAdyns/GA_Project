#include "Game.h"
#include "DrawFloatToInt.h"

void Game::Initialize()
{
	//BaseGame::Initialize();
	ENGINE.SetBackGroundColor(RGB(0, 0, 134));
	pointToMove = {ENGINE.GetWindowRect().width / 2 - 100.f, ENGINE.GetWindowRect().height / 2.f,0.f, 1.f };
	reflectedPointToMove = { pointToMove };
	m_Position = { 20,20,0,1 };
}
void Game::Cleanup()
{
}
void Game::Draw() const
{
	m_Level.Draw();
	OneBlade plane{ 250,0,0,1 };

	ThreeBlade point{ 250, 250, 0, 1 };

	//ENGINE.DrawEllipse(point[0], point[1], 5,5);
	////ENGINE.DrawEllipse(GetViewPort().width/2, GetViewPort().height/2, 50, 50);
	Drawf::DrawEllipse(pointToMove[0], pointToMove[1], 25, 25);
	Drawf::DrawEllipse(reflectedPointToMove[0], reflectedPointToMove[1], 25, 25);
	//ENGINE.DrawEllipse(m_Position[0], m_Position[1], 25, 25);
	//ENGINE.DrawLine(0, 0, point[0], point[1]);
	//ENGINE.DrawRectangle(RectInt{ plane[0] - 50, 50, 100,100 });
}
void Game::Tick()
{
	m_Level.Update();

	Motor trans{ Motor::Translation(80 * ENGINE.GetDeltaTime(), TwoBlade{0,1,0,0,0,0})};
	m_Position = (trans * m_Position * ~trans).Grade3();

	OneBlade e1{ -ENGINE.GetWindowRect().width / 2.f,1,0,0 };
	OneBlade e2{ -ENGINE.GetWindowRect().height / 2.f,0,1,0 };

	auto line = e1 ^ e2;
	float angleForPoint = 60 * ENGINE.GetDeltaTime();

	//Motor rotator{0,0,20,30,0,60,70,0};
	Motor rot = Motor::Rotation(angleForPoint, line);
	//rot.Normalize();
	//rotator[0] = cos(angleForPoint * DEG_TO_RAD/2);
	//rotator += -(sin(angleForPoint * DEG_TO_RAD/2) * line);
	//rotator.Normalize();

	pointToMove = (rot * pointToMove * ~rot).Grade3();
	reflectedPointToMove = (line * pointToMove * ~line).Grade3();
}
void Game::KeyDown(int virtualKeycode)
{

	// Numbers and letters from '0' to '9' and 'A' to 'Z' are represented by their ASCII values
	// For example: if(virtualKeycode == 'B')
	// BE CAREFULL! Don't use lower caps, because those have different ASCII values
	//
	// Other keys are checked with their virtual Keycode defines
	// For example: if(virtualKeycode == VK_MENU)
	// VK_MENU represents the 'Alt' key
	//
	// Click here for more information: https://learn.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

}
void Game::KeyDownThisFrame(int virtualKeycode)
{
	// Numbers and letters from '0' to '9' and 'A' to 'Z' are represented by their ASCII values
	// For example: if(virtualKeycode == 'B')
	// BE CAREFULL! Don't use lower caps, because those have different ASCII values
	//
	// Other keys are checked with their virtual Keycode defines
	// For example: if(virtualKeycode == VK_MENU)
	// VK_MENU represents the 'Alt' key
	//
	// Click here for more information: https://learn.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

	m_Level.InputKeyDownThisFrame(virtualKeycode);
}
void Game::KeyUp(int virtualKeycode)
{
	m_Level.InputKeyUp(virtualKeycode);
	// Numbers and letters from '0' to '9' and 'A' to 'Z' are represented by their ASCII values
	// For example: if(virtualKeycode == 'B')
	// BE CAREFULL! Don't use lower caps, because those have different ASCII values
	//
	// Other keys are checked with their virtual Keycode defines
	// For example: if(virtualKeycode == VK_MENU)
	// VK_MENU represents the 'Alt' key
	//
	// Click here for more information: https://learn.microsoft.com/en-us/windows/win32/learnwin32/keyboard-input

}
void Game::HandleControllerInput()
{
}
void Game::MouseDown(bool isLeft, int x, int y)
{

}
void Game::MouseUp(bool isLeft, int x, int y)
{
	
}
void Game::MouseMove(int x, int y, int keyDown)
{
	//See this link to check which keys could be represented in the keyDown parameter
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove
}
void Game::MouseWheelTurn(int x, int y, int turnDistance, int keyDown)
{
	//See this link to check which keys could be represented in the keyDown parameter and what the turnDistance is for
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousewheel
}