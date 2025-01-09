#include "HUD.h"
#include "DrawFloatToInt.h"
#include "RotatorUnit.h"
#include "TeleportUnit.h"
#include "BoosterUnit.h"
#include "PhaserUnit.h"


HUD::HUD()
{
	m_VecUnitsToSelect.emplace_back(std::make_unique<RotatorUnit>(0.f, 0.f));
	m_VecUnitsToSelect.emplace_back(std::make_unique<TeleportUnit>(0.f, 0.f));
	m_VecUnitsToSelect.emplace_back(std::make_unique<BoosterUnit>(0.f, 0.f));
	m_VecUnitsToSelect.emplace_back(std::make_unique<PhaserUnit>(0.f, 0.f));

	float spaceBetween = m_Area.width / (static_cast<int>(m_VecUnitsToSelect.size()) + 1);

	for (size_t i = 0; i < m_VecUnitsToSelect.size(); i++)
	{
		TwoBlade transLine{1,0,0,0,0,0};
		Motor trans = Motor::Translation(m_Area.left + spaceBetween + spaceBetween * i, transLine);
		m_VecUnitsToSelect[i]->TranslateUnit(trans);

		transLine = { 0,1,0,0,0,0 };
		trans = Motor::Translation(m_Area.bottom + m_AreaHeight / 2, transLine);
		m_VecUnitsToSelect[i]->TranslateUnit(trans);
	}
}

void HUD::Draw() const
{
	ENGINE.SetColor(RGB(20, 20, 20));
	Drawf::FillRectangle(m_Area);
	ENGINE.SetColor(RGB(0, 0, 0));
	Drawf::DrawRectangle(m_Area,5);

	for (const auto& pUnit : m_VecUnitsToSelect)
	{
		pUnit->Draw();
	}
	auto squareSize{ m_AreaHeight - 5 };
	auto unitPos = m_VecUnitsToSelect[m_IndexSelectedUnit]->GetPos();
	ENGINE.SetColor(RGB(0, 220, 0));
	Drawf::DrawRectangle(unitPos.x - squareSize / 2, unitPos.y - squareSize / 2, squareSize, squareSize, 2.f);
}

void HUD::SelectNextUnit()
{
	++m_IndexSelectedUnit;
	if (m_IndexSelectedUnit >= m_VecUnitsToSelect.size())
		m_IndexSelectedUnit = 0;
}

void HUD::SelectPreviousUnit()
{
	--m_IndexSelectedUnit;
	if (m_IndexSelectedUnit < 0)
		m_IndexSelectedUnit = static_cast<int>(m_VecUnitsToSelect.size()) - 1;
}

std::unique_ptr<Unit> HUD::GetInstaceOfSelectedUnit(const Point2f& pos) const
{
	auto typeID = m_VecUnitsToSelect[m_IndexSelectedUnit]->GetTypeId();
	if (typeid(RotatorUnit) == typeID)
	{
		return ((m_VecUnitsToSelect[m_IndexSelectedUnit])->CreateUnit<RotatorUnit>(pos));
	}
	if (typeid(TeleportUnit) == typeID)
	{
		return ((m_VecUnitsToSelect[m_IndexSelectedUnit])->CreateUnit<TeleportUnit>(pos));
	}
	if (typeid(BoosterUnit) == typeID)
	{
		return ((m_VecUnitsToSelect[m_IndexSelectedUnit])->CreateUnit<BoosterUnit>(pos));
	}
	if (typeid(PhaserUnit) == typeID)
	{
		return ((m_VecUnitsToSelect[m_IndexSelectedUnit])->CreateUnit<PhaserUnit>(pos));
	}

	return nullptr;
}
