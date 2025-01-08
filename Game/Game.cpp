#include "Game.h"
#include "DrawFloatToInt.h"

void Game::Initialize()
{
	ENGINE.SetBackGroundColor(RGB(0, 0, 134));
	LoadScreen();
}
void Game::Cleanup()
{
}
void Game::Draw() const
{
	DrawScreens();
}
void Game::Tick()
{
	if (m_UpdateScreen) HandleEventQueue();
	m_pScreenStack.back().second->Update();

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

	m_pScreenStack.back().second->InputKeyDownThisFrame(virtualKeycode);
}
void Game::KeyUp(int virtualKeycode)
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

	m_pScreenStack.back().second->InputKeyUp(virtualKeycode);
}
void Game::HandleControllerInput()
{
	m_pScreenStack.back().second->HandleControllerInput();
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

void Game::SetScreen(State newState)
{
	m_GameState = newState;
}

void Game::AddOperationToQueue(ScreenOperation screenOper)
{
	m_ScreenEventQueue.emplace(m_GameState, screenOper);
	m_UpdateScreen = true;
}

void Game::LoadScreen()
{
	for (int i{ static_cast<int>(m_pScreenStack.size() - 1) }; i >= 0; --i)
	{
		m_pScreenStack.at(i).second->OnExit();
	}
	m_pScreenStack.clear();

	switch (m_GameState)
	{

	case State::Playing:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<LevelScreen>(*this));

		break;

	}

	m_pScreenStack.back().second->OnEnter();

	m_UpdateScreen = false;
}
void Game::PushScreen()
{
	m_pScreenStack.back().second->OnSuspend();
	switch (m_GameState)
	{

	case State::Playing:

		m_pScreenStack.emplace_back(m_GameState, std::make_unique<LevelScreen>(*this));

		break;
	
	}

	m_pScreenStack.back().second->OnEnter();

}

void Game::PopScreen()
{
	m_pScreenStack.back().second->OnExit();

	m_pScreenStack.pop_back();

	m_pScreenStack.back().second->OnResume();
	m_GameState = m_pScreenStack.back().first;
}
void Game::DrawScreens() const
{
	for (const auto& [gameState, pScreen] : m_pScreenStack)
	{
		pScreen->Draw();
	}
}

void Game::HandleEventQueue()
{
	while (not m_ScreenEventQueue.empty())
	{
		auto [gameState, screenOperation] = m_ScreenEventQueue.front();
		m_ScreenEventQueue.pop();

		switch (screenOperation)
		{
		case Game::ScreenOperation::Set:
			m_GameState = gameState;
			LoadScreen();
			break;
		case Game::ScreenOperation::Push:
			m_GameState = gameState;
			PushScreen();
			break;
		case Game::ScreenOperation::Pop:
			PopScreen();
			break;
		}
	}

	m_UpdateScreen = false;
}
