#include "TeleportUnit.h"
#include "FlyFish.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"

TeleportUnit::TeleportUnit(const Point2f& pos) :
	TeleportUnit{ pos.x, pos.y }
{

}
TeleportUnit::TeleportUnit(float x, float y) :
	Unit{ Point2f{x, y} }
{
}

std::unique_ptr<Unit> TeleportUnit::CreateUnit(const Point2f& pos)
{
	return std::make_unique<TeleportUnit>(pos);
}

void TeleportUnit::Draw() const
{
	constexpr float mirrorThickness{ 10 };

	ENGINE.SetColor(m_Color, 1.f);
	Drawf::FillRoundedRect(m_Position.x - m_Width / 2, m_Position.y - mirrorThickness / 2, m_Width, mirrorThickness, mirrorThickness, mirrorThickness/4);
	Drawf::DrawRectangle(m_Position.x - m_Width / 2, m_Position.y - m_Height / 2 + m_Height, m_Width, m_Height);

	ENGINE.SetColor(m_Color, 0.5f);
	Drawf::FillRectangle(m_Position.x - m_Width / 2, m_Position.y - m_Height / 2 - m_Height, m_Width, m_Height);	

}

void TeleportUnit::Update()
{
}

void TeleportUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	if (m_ActivationBox.IsPointInside(pProjectile->GetPoint()))
	{
		pProjectile->SetPoint((m_ReflectPlane * pProjectile->GetPoint() * ~m_ReflectPlane).Normalized().Grade3());
	}
		
}

void TeleportUnit::Action1()
{
	const ThreeBlade pos{ m_Position.x, m_Position.y, 0 };
	const TwoBlade rotLine{ TwoBlade::LineFromPoints(pos[0], pos[1], pos[2], pos[0], pos[1], pos[2] + 1) };
	const float degreesStep{ 90 };

	GAUtils::RotatePlane(m_ReflectPlane, degreesStep, rotLine);
	GAUtils::RotatePlane(m_ActivationBox.m_LeftSide, degreesStep, rotLine);
	GAUtils::RotatePlane(m_ActivationBox.m_RightSide, degreesStep, rotLine);
	GAUtils::RotatePlane(m_ActivationBox.m_BottomSide, degreesStep, rotLine);
	GAUtils::RotatePlane(m_ActivationBox.m_TopSide, degreesStep, rotLine);
}
