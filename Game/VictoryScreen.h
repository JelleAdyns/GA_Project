#ifndef VICTORYSCREEN_H
#define VICTORYSCREEN_H

#include <vector>
#include <Engine.h>
#include "Screen.h"
#include "Box.h"
#include "FlyFish.h"
#include "Commands.h"

class Game;
class VictoryScreen final : public Screen
{
public:
	VictoryScreen(Game& game) :
		Screen{},
		m_rTitleFont{ jela::ResourceManager::GetInstance().GetFont(_T("Showcard Gothic")) },
		m_ScreenBox{
			ENGINE.GetWindowRect().width / 2.f,
			ENGINE.GetWindowRect().height / 2.f,
			static_cast<float>(ENGINE.GetWindowRect().width),
			static_cast<float>(ENGINE.GetWindowRect().height) },
			m_pMainMenuCommand{ std::make_unique<LoadScreenCommand>(game, Game::State::MainMenu) }
	{
		m_rTitleFont.SetTextFormat(100, true, false);
		m_rTitleFont.SetHorizontalAllignment(jela::Font::HorAllignment::Center);
		m_rTitleFont.SetVerticalAllignment(jela::Font::VertAllignment::Center);
	}

	~VictoryScreen() = default;

	VictoryScreen(const VictoryScreen& other) = delete;
	VictoryScreen(VictoryScreen&& other) noexcept = delete;
	VictoryScreen& operator=(const VictoryScreen& other) = delete;
	VictoryScreen& operator=(VictoryScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update() override;

	virtual void InputKeyDownThisFrame(int virtualKeyCode) override;
	virtual void InputKeyUp(int virtualKeyCode) override;
	virtual void HandleControllerInput() override {};

	virtual void OnEnter() override {};
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};


private:

	jela::Font& m_rTitleFont;

	const Box m_ScreenBox;

	std::vector<ThreeBlade> m_VecPoints;

	std::unique_ptr<Command> m_pMainMenuCommand;

	void EraseLostPoints();
};

#endif // !VICTORYSCREEN_H