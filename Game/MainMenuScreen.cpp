#include "MainMenuScreen.h"
#include "GAUtils.h"
#include "DrawFloatToInt.h"
#include <algorithm>

void MainMenuScreen::Draw() const
{
	float screenRadius{ m_ScreenBox.GetWidth() /2 };
	ThreeBlade middlePoint{ m_ScreenBox.GetWidth() / 2, m_ScreenBox.GetHeight() / 2,0 };
	for (const auto& point : m_VecPoints)
	{
		float dist = GAUtils::GetDistance(point, middlePoint);
		int rValue = 100+static_cast<int>((dist / (screenRadius/3)) * 255);
		int gValue = 100+static_cast<int>(((dist - screenRadius / 3 ) / (screenRadius/3)) * 255);
		int bValue = 100+static_cast<int>(((dist - screenRadius / 3* 2)/ (screenRadius/3)) * 255);
		ENGINE.SetColor(
			RGB(
				std::max<int>(std::min<int>(rValue, 255), 0),
				std::max<int>(std::min<int>(gValue, 255), 0),
				std::max<int>(std::min<int>(bValue, 255), 0)
			)
		);

		Drawf::FillEllipse(point[0], point[1], 10, 10);
		ENGINE.SetColor(RGB(0,0,0));
		Drawf::DrawEllipse(point[0], point[1], 10, 10);
	}
	ENGINE.SetColor(RGB(255, 255, 0));
	ENGINE.DrawString(
		_T("In Plane Sight"),
		m_rTitleFont,
		0,
		ENGINE.GetWindowRect().width-100,
		ENGINE.GetWindowRect().width);
}

void MainMenuScreen::Update()
{
	static float fireRate{ 1.f };
	static float time{ 1.f };
	time += ENGINE.GetDeltaTime();
	if (time >= fireRate)
	{
		m_VecPoints.emplace_back(ThreeBlade{ m_ScreenBox.GetWidth() / 2 + 1, m_ScreenBox.GetHeight() / 2,0 });
		m_VecPoints.emplace_back(ThreeBlade{ m_ScreenBox.GetWidth() / 2, m_ScreenBox.GetHeight() / 2 + 1,0 });
		m_VecPoints.emplace_back(ThreeBlade{ m_ScreenBox.GetWidth() / 2 - 1, m_ScreenBox.GetHeight() / 2,0 });
		m_VecPoints.emplace_back(ThreeBlade{ m_ScreenBox.GetWidth() / 2, m_ScreenBox.GetHeight() / 2 - 1,0 });

		time -= fireRate;
	}

	ThreeBlade middlePoint{ m_ScreenBox.GetWidth() / 2, m_ScreenBox.GetHeight() / 2,0 };
	TwoBlade rotLine = TwoBlade::LineFromPoints(
		middlePoint[0], middlePoint[1], middlePoint[2],
		middlePoint[0], middlePoint[1], middlePoint[2] + 1);
	for (auto& point : m_VecPoints)
	{
		auto rot = Motor::Rotation(20*ENGINE.GetDeltaTime(), rotLine);
		GAUtils::Transform(point, rot);

		TwoBlade trLine = OneBlade{ -1,0,0,0 } ^ ((middlePoint & point) | point);
		auto tr = Motor::Translation(30 * ENGINE.GetDeltaTime(), trLine);
		GAUtils::Transform(point, tr);
		
	}

	EraseLostPoints();
}

void MainMenuScreen::InputKeyDownThisFrame(int virtualKeyCode)
{
	if (virtualKeyCode != VK_F11)
		m_pStartCommand->Execute();
}

void MainMenuScreen::InputKeyUp(int virtualKeyCode)
{
	
}

void MainMenuScreen::EraseLostPoints()
{
	m_VecPoints.erase(
		std::remove_if(
			m_VecPoints.begin(),
			m_VecPoints.end(),
			[&](const ThreeBlade& point)
			{
				return m_ScreenBox.GetDistanceFromLeft(point) < -100;
			}),
		m_VecPoints.end()
	);
}
