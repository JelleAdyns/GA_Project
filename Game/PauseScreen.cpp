#include "PauseScreen.h"

PauseScreen::PauseScreen(Game& game) :
	Screen{},
	m_pPopScreen{ std::make_unique<PopScreenCommand>(game) },
	m_pLoadTitleScreen{std::make_unique<LoadScreenCommand>(game, Game::State::MainMenu) }
{
	
}

void PauseScreen::Draw() const
{
	const auto& wndwRect = ENGINE.GetWindowRect();
	constexpr int margin = 40;
	constexpr int textMargin = 15;
	constexpr int height = 450;
	const jela::RectInt destRect{ margin, (wndwRect.height - height) / 2, wndwRect.width - margin * 2, height };

	ENGINE.SetColor(RGB(0, 0, 0), 0.3f);
	ENGINE.FillRectangle(wndwRect);
	ENGINE.SetColor(RGB(0, 0, 0), 0.5f);
	ENGINE.FillRectangle(destRect);
	
	const jela::RectInt textDestRect{ destRect.left + textMargin, destRect.bottom + textMargin, destRect.width - textMargin * 2, destRect.height - textMargin * 2 };
	ENGINE.SetColor(RGB(0, 0, 0));
	ENGINE.DrawRectangle(destRect);
	ENGINE.SetColor(RGB(255, 255, 255));


	m_rFont.SetTextFormat(32, true, false);
	m_rFont.SetHorizontalAllignment(jela::Font::HorAllignment::Center);
	m_rFont.SetVerticalAllignment(jela::Font::VertAllignment::Top);

	ENGINE.DrawString(_T("PAUSE"), m_rFont, textDestRect);

	m_rFont.SetHorizontalAllignment(jela::Font::HorAllignment::Left);
	m_rFont.SetVerticalAllignment(jela::Font::VertAllignment::Center);

	ENGINE.DrawString(
		_T("Move:\nPlayer boost:\nSelect unit:\nPlace unit:\nPick up unit:\nModify units:\nHands free:"),
		m_rFont,
		textDestRect);

	ENGINE.DrawString(
		_T("WASD\nSHIFT\nQ/E\nSPACE (not in tiles)\nX (when in range)\nARROWS\nR"),
		m_rFont,
		textDestRect.left + textDestRect.width/2,
		textDestRect.bottom,
		textDestRect.width/2,
		textDestRect.height);

	m_rFont.SetHorizontalAllignment(jela::Font::HorAllignment::Center);
	m_rFont.SetVerticalAllignment(jela::Font::VertAllignment::Center);

	ENGINE.DrawString(_T("Main Menu: BACKSPACE"),
		m_rFont,
		destRect.left + textMargin,
		destRect.bottom + textMargin,
		destRect.width - textMargin * 2);
}

void PauseScreen::Update()
{
}

void PauseScreen::InputKeyDownThisFrame(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case VK_ESCAPE:
		m_pPopScreen->Execute();
		break;
	case VK_BACK:
		m_pLoadTitleScreen->Execute();
		break;
	}
}

void PauseScreen::InputKeyUp(int virtualKeyCode)
{
}

void PauseScreen::HandleControllerInput()
{
}

