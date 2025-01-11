#include "HUD.h"
#include "DrawFloatToInt.h"
#include "RotatorUnit.h"
#include "TeleportUnit.h"
#include "BoosterUnit.h"
#include "PhaserUnit.h"
#include <algorithm>


HUD::HUD()
{
	m_rFont.SetTextFormat(32, true, false);
	m_rFont.SetHorizontalAllignment(jela::Font::HorAllignment::Left);
	m_rFont.SetVerticalAllignment(jela::Font::VertAllignment::Bottom);

	m_VecUnits.emplace_back(std::make_unique<RotatorUnit>(0.f, 0.f),7);
	m_VecUnits.emplace_back(std::make_unique<TeleportUnit>(0.f, 0.f),4);
	m_VecUnits.emplace_back(std::make_unique<BoosterUnit>(0.f, 0.f),5);
	m_VecUnits.emplace_back(std::make_unique<PhaserUnit>(0.f, 0.f),2);

	float spaceBetween = m_Area.width / (static_cast<int>(m_VecUnits.size()) + 1);

	for (size_t i = 0; i < m_VecUnits.size(); i++)
	{
		TwoBlade transLine{1,0,0,0,0,0};
		Motor trans = Motor::Translation(m_Area.left + spaceBetween + spaceBetween * i, transLine);
		m_VecUnits[i].pUnit->TranslateUnit(trans);

		transLine = { 0,1,0,0,0,0 };
		trans = Motor::Translation(m_Area.bottom + m_AreaHeight / 2, transLine);
		m_VecUnits[i].pUnit->TranslateUnit(trans);
	}
}

void HUD::Draw() const
{
	ENGINE.SetColor(RGB(20, 20, 20), 0.9f);
	Drawf::FillRectangle(m_Area);
	ENGINE.SetColor(RGB(0, 0, 0));
	Drawf::DrawRectangle(m_Area,5);

	auto squareSize{ m_AreaHeight - 10 };
	auto unitPos = m_VecUnits[m_SelectedIndex].pUnit->GetPos();
	Rectf destrect{ unitPos[0] - squareSize / 2, unitPos[1] - squareSize / 2, squareSize, squareSize };

	ENGINE.SetColor(RGB(0, 220, 0));
	Drawf::DrawRectangle(destrect, 2.f);

	for (const auto& availableUnit : m_VecUnits)
	{
		unitPos = availableUnit.pUnit->GetPos();
		destrect = Rectf{ unitPos[0] - squareSize / 2 + 5, unitPos[1] - squareSize / 2, squareSize, squareSize };
		availableUnit.pUnit->Draw();
		ENGINE.SetColor(RGB(235, 235, 235));
		Drawf::DrawString(to_tstring(availableUnit.CurrentAmountLeft), m_rFont, destrect);
	}
	
}

void HUD::SelectNextUnit()
{
	++m_SelectedIndex;
	if (m_SelectedIndex >= m_VecUnits.size())
		m_SelectedIndex = 0;
}

void HUD::SelectPreviousUnit()
{
	--m_SelectedIndex;
	if (m_SelectedIndex < 0)
		m_SelectedIndex = static_cast<int>(m_VecUnits.size()) - 1;
}

void HUD::Reset()
{
	m_VecUnits.clear();
	m_SelectedIndex = 0;
}

void HUD::DecreaseAmountAvailable()
{
	m_VecUnits[m_SelectedIndex].CurrentAmountLeft =
		std::max<int>(m_VecUnits[m_SelectedIndex].CurrentAmountLeft - 1, 0);
}

void HUD::IncreaseAmountAvailable()
{
	m_VecUnits[m_SelectedIndex].CurrentAmountLeft =
		std::min<int>(m_VecUnits[m_SelectedIndex].CurrentAmountLeft + 1, m_VecUnits[m_SelectedIndex].MaxAmount);
}

bool HUD::IsSameUnit(std::type_index typeId) const
{
	return m_VecUnits[m_SelectedIndex].pUnit->GetTypeId() == typeId;
}

bool HUD::IsUnitAvailable() const
{
	return m_VecUnits[m_SelectedIndex].CurrentAmountLeft > 0;
}

std::unique_ptr<Unit> HUD::GetInstaceOfSelectedUnit(const Point2f& pos) const
{
	auto typeID = m_VecUnits[m_SelectedIndex].pUnit->GetTypeId();
	if (typeid(RotatorUnit) == typeID)
	{
		return Unit::CreateUnit<RotatorUnit>(pos);
	}
	if (typeid(TeleportUnit) == typeID)
	{
		return Unit::CreateUnit<TeleportUnit>(pos);
	}
	if (typeid(BoosterUnit) == typeID)
	{
		return Unit::CreateUnit<BoosterUnit>(pos);
	}
	if (typeid(PhaserUnit) == typeID)
	{
		return Unit::CreateUnit<PhaserUnit>(pos);
	}

	return nullptr;
}
