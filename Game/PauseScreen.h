#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Screen.h"
#include "Commands.h"
#include "Game.h"

class PauseScreen final : public Screen
{
public:
	explicit PauseScreen(Game& game);
	virtual ~PauseScreen() = default;

	PauseScreen(const PauseScreen& other) = delete;
	PauseScreen(PauseScreen&& other) noexcept = delete;
	PauseScreen& operator=(const PauseScreen& other) = delete;
	PauseScreen& operator=(PauseScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void InputKeyDownThisFrame(int virtualKeyCode) override;
	virtual void InputKeyUp(int virtualKeyCode) override;
	virtual void HandleControllerInput() override;

	virtual void OnEnter() override {};
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};
private:

	std::unique_ptr<Command> m_pPopScreen;
	std::unique_ptr<Command> m_pLoadTitleScreen;

	jela::Font& m_rFont{ jela::ResourceManager::GetInstance().GetFont(_T("Arial")) };
	
};

#endif // !PAUSESCREEN_H