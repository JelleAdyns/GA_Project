#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include <vector>
#include <Engine.h>
#include "Screen.h"
#include "Box.h"
#include "FlyFish.h"
#include "Commands.h"

class Game;
class MainMenuScreen final : public Screen
{
public:
	MainMenuScreen(Game& game) :
		Screen{},
		m_rTitleFont{jela::ResourceManager::GetInstance().GetFont(_T("Showcard Gothic"))},
		m_ScreenBox{
			ENGINE.GetWindowRect().width / 2.f,
			ENGINE.GetWindowRect().height/ 2.f,
			static_cast<float>(ENGINE.GetWindowRect().width),
			static_cast<float>(ENGINE.GetWindowRect().height) },
		m_pStartCommand{std::make_unique<LoadScreenCommand>(game, Game::State::Playing)}
	{
		m_rTitleFont.SetTextFormat(100, true, false);
		m_rTitleFont.SetHorizontalAllignment(jela::Font::HorAllignment::Center);
		m_rTitleFont.SetVerticalAllignment(jela::Font::VertAllignment::Center);
	}

	~MainMenuScreen() = default;

	MainMenuScreen(const MainMenuScreen& other) = delete;
	MainMenuScreen(MainMenuScreen&& other) noexcept = delete;
	MainMenuScreen& operator=(const MainMenuScreen& other) = delete;
	MainMenuScreen& operator=(MainMenuScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update() override;

	virtual void InputKeyDownThisFrame(int virtualKeyCode) override {};
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

	std::unique_ptr<Command> m_pStartCommand;

	void EraseLostPoints();
};

#endif // !MAINMENUSCREENH