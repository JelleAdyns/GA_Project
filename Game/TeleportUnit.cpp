#include "TeleportUnit.h"
#include "FlyFish.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"

TeleportUnit::TeleportUnit(const Point2f& pos) :
	TeleportUnit{ pos.x, pos.y }
{
}
TeleportUnit::TeleportUnit(float x, float y) :
	Unit{ x, y }
{
	const ThreeBlade p{ x, y, 0 };
	const TwoBlade rotLine{ TwoBlade::LineFromPoints(p[0], p[1], p[2], p[0], p[1], p[2] + 1) };
	Motor rotation = Motor::Rotation(180, rotLine);
	m_DestinationBox.Rotate(rotation, true);
}

void TeleportUnit::Draw() const
{
	constexpr float mirrorThickness{ 10 };

	ENGINE.SetColor(m_Color, 1.f);
	Drawf::FillRoundedRect(m_Position[0] - m_Width / 2, m_Position[1] - mirrorThickness / 2, m_Width, mirrorThickness, mirrorThickness, mirrorThickness/4);

	std::vector<Point2f> activateAreaPoints{};
	m_DestinationBox.GetCornerPoints(activateAreaPoints);
	Drawf::DrawPolygon(activateAreaPoints, 2.f, true);

	ENGINE.SetColor(m_Color, 0.5f);

	activateAreaPoints.clear();
	m_ActivationBox.GetCornerPoints(activateAreaPoints);
	Drawf::FillPolygon(activateAreaPoints);

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
	const TwoBlade rotLine{ TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, m_Position[0], m_Position[1], 1) };
	const float degreesStep{ 45 };

	Motor rotation = Motor::Rotation(degreesStep, rotLine);
	GAUtils::Transform(m_ReflectPlane, rotation);
	m_ActivationBox.Rotate(rotation, true);
	m_DestinationBox.Rotate(rotation, true);
}

void TeleportUnit::TranslateUnit(const Motor& translation)
{
	GAUtils::Transform(m_ReflectPlane, translation);
	m_ActivationBox.Translate(translation);
	m_DestinationBox.Translate(translation);

	GAUtils::Transform(m_Position, translation);
}
