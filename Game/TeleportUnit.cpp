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
	Unit::Draw();

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
	Rotate(m_DegreesStep);
}

void TeleportUnit::Action2()
{
	Rotate(-m_DegreesStep);
}

void TeleportUnit::Action3()
{
	ApplyOffset(m_OffsetStep);
}

void TeleportUnit::Action4()
{
	ApplyOffset(-m_OffsetStep);
}

void TeleportUnit::TranslateUnit(const Motor& translation)
{
	GAUtils::Transform(m_ReflectPlane, translation);
	m_ActivationBox.Translate(translation);
	m_DestinationBox.Translate(translation);

	GAUtils::Transform(m_Position, translation);
}

void TeleportUnit::Rotate(float degrees)
{
	const TwoBlade rotLine{ TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, m_Position[0], m_Position[1], 1) };
	
	Motor rotation = Motor::Rotation(degrees, rotLine);
	GAUtils::Transform(m_ReflectPlane, rotation);
	m_ActivationBox.Rotate(rotation, true);
	m_DestinationBox.Rotate(rotation, true);
}

void TeleportUnit::ApplyOffset(float dist)
{
	const TwoBlade trLine{ m_ReflectPlane ^ OneBlade{-1,0,0,0} };

	m_ActivationBox.Translate(Motor::Translation(dist, trLine));
	m_DestinationBox.Translate(Motor::Translation(dist, -trLine));

	float currentDistance = GAUtils::GetDistance(m_ActivationBox.Center, m_ReflectPlane);
	if ((dist > 0.f and currentDistance >= m_MaxDistFromPlane))
	{
		m_ActivationBox.Translate(Motor::Translation(m_MaxDistFromPlane - currentDistance, trLine));
		m_DestinationBox.Translate(Motor::Translation(m_MaxDistFromPlane - currentDistance, -trLine));
		return;
	}
	
	if(dist < 0.f and currentDistance <= m_MinDistFromPlane)
	{
		m_ActivationBox.Translate(Motor::Translation(m_MinDistFromPlane - currentDistance, trLine));
		m_DestinationBox.Translate(Motor::Translation(m_MinDistFromPlane - currentDistance, -trLine));
		return;
	}


}
