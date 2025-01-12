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
	Drawf::FillEllipse(m_Position[0], m_Position[1],5,5);

	std::vector<Point2f> activateAreaPointsAct{};
	m_DestinationBox.GetCornerPoints(activateAreaPointsAct);
	Drawf::DrawPolygon(activateAreaPointsAct, 2.f, true);

	ENGINE.SetColor(m_Color, 0.5f);

	std::vector<Point2f> activateAreaPointsDest{};
	m_ActivationBox.GetCornerPoints(activateAreaPointsDest);
	Drawf::FillPolygon(activateAreaPointsDest);

	ENGINE.SetColor(m_Color, 1.f);
	Drawf::DrawLine(activateAreaPointsAct[0], activateAreaPointsDest[0], 2.f);
	Drawf::DrawLine(activateAreaPointsAct[1], activateAreaPointsDest[1], 2.f);

}

void TeleportUnit::Update()
{
}

void TeleportUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	if (m_ActivationBox.IsPointInside(pProjectile->GetPoint()))
	{
		pProjectile->SetPoint((m_Position * pProjectile->GetPoint() * ~m_Position).Normalized().Grade3());
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
	//GAUtils::Transform(m_ReflectPlane, translation);
	m_ActivationBox.Translate(translation);
	m_DestinationBox.Translate(translation);

	GAUtils::Transform(m_Position, translation);
}

void TeleportUnit::Rotate(float degrees)
{
	const TwoBlade rotLine{ TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, m_Position[0], m_Position[1], 1) };
	
	Motor rotation = Motor::Rotation(degrees, rotLine);
	//GAUtils::Transform(m_ReflectPlane, rotation);
	m_ActivationBox.Rotate(rotation, true);
	m_DestinationBox.Rotate(rotation, true);
}

void TeleportUnit::ApplyOffset(float dist)
{
	//const TwoBlade trLine{ m_ReflectPlane ^ OneBlade{-1,0,0,0} };
	const TwoBlade trLine{ (m_ActivationBox.TopSide ^ m_DestinationBox.TopSide).Normalized()};

	m_ActivationBox.Translate(Motor::Translation(dist, trLine));
	m_DestinationBox.Translate(Motor::Translation(dist, -trLine));

	float currentDistance = GAUtils::GetDistance(m_ActivationBox.Center, m_Position);
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
