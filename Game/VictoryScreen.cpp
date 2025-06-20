#include "VictoryScreen.h"
#include "GAUtils.h"
#include "DrawFloatToInt.h"
#include <algorithm>

void VictoryScreen::Draw() const
{
	m_rTitleFont.SetTextFormat(100, true, false);
	float screenRadius{ m_ScreenBox.GetWidth() / 2 };
	ThreeBlade middlePoint{ m_ScreenBox.GetWidth() / 2, m_ScreenBox.GetHeight() / 2,0 };
	for (const auto& point : m_VecPoints)
	{
		float dist = GAUtils::GetDistance(point, middlePoint);
		int rValue = 100 + static_cast<int>((dist / (screenRadius / 3)) * 255);
		int gValue = 100 + static_cast<int>(((dist - screenRadius / 3) / (screenRadius / 3)) * 255);
		int bValue = 100 + static_cast<int>(((dist - screenRadius / 3 * 2) / (screenRadius / 3)) * 255);
		ENGINE.SetColor(
			RGB(
				std::max<int>(std::min<int>(rValue, 255), 0),
				std::max<int>(std::min<int>(gValue, 255), 0),
				std::max<int>(std::min<int>(bValue, 255), 0)
			)
		);

		Drawf::FillEllipse(point[0], point[1], 10, 10);
		ENGINE.SetColor(RGB(0, 0, 0));
		Drawf::DrawEllipse(point[0], point[1], 10, 10);
	}

	ENGINE.SetColor(RGB(255, 255, 0));
	constexpr int hintWidth{ 600 };
	ENGINE.DrawString(_T("VICTORY!"), m_rTitleFont, ENGINE.GetWindowRect().width / 2 - hintWidth / 2, ENGINE.GetWindowRect().height / 2 -50, hintWidth);
	
}

void VictoryScreen::Update()
{
	
	ThreeBlade middlePoint{ m_ScreenBox.GetWidth() / 2, m_ScreenBox.GetHeight() / 2,0 };
	static float fireRate{ 0.75f };
	static float time{ fireRate };
	time += ENGINE.GetDeltaTime();

	if (time >= fireRate)
	{
		TwoBlade rotLine = TwoBlade::LineFromPoints(
		middlePoint[0], middlePoint[1], middlePoint[2],
		middlePoint[0], middlePoint[1], middlePoint[2] + 1);
		
		int nrOfPoints{ 30 };
		for (size_t i = 0; i < nrOfPoints; i++)
		{
			ThreeBlade point{ m_ScreenBox.GetWidth() / 2 + 1, m_ScreenBox.GetHeight() / 2,0 };
			auto rot = Motor::Rotation(i*(360.f/ nrOfPoints), rotLine);
			GAUtils::Transform(point, rot);
			m_VecPoints.emplace_back(point);
		}

		time -= fireRate;
	}

	for (auto& point : m_VecPoints)
	{
		TwoBlade trLine = OneBlade{ -1,0,0,0 } ^ ((middlePoint & point) | point);
		auto tr = Motor::Translation(60 * ENGINE.GetDeltaTime(), trLine);
		GAUtils::Transform(point, tr);
	}

	EraseLostPoints();
}

void VictoryScreen::InputKeyDownThisFrame(int virtualKeyCode)
{
	if (virtualKeyCode != VK_F11)
		m_pMainMenuCommand->Execute();
}

void VictoryScreen::InputKeyUp(int virtualKeyCode)
{

}

void VictoryScreen::EraseLostPoints()
{
	m_VecPoints.erase(
		std::remove_if(
			m_VecPoints.begin(),
			m_VecPoints.end(),
			[&](const ThreeBlade& point)
			{
				return not m_ScreenBox.IsPointInside(point, 10);
			}),
		m_VecPoints.end()
	);
}
