#include "RotatorUnit.h"
#include "FlyFish.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"

RotatorUnit::RotatorUnit(const Point2f& pos) :
	RotatorUnit{ pos.x, pos.y }
{

}
RotatorUnit::RotatorUnit(float x, float y):
	Unit{ x, y },
	m_RotationLine{ TwoBlade::LineFromPoints(x,y,0, x,y,1) }
{
}

void RotatorUnit::Draw() const
{
	Unit::Draw();

	ENGINE.SetColor(m_Color, 0.5f);
	Drawf::FillArc(m_Position[0], m_Position[1], m_Radius, m_Radius, m_StartAngle, m_Degrees);
	ENGINE.SetColor(RGB(255,0,0), 0.5f);
	Drawf::DrawArc(m_Position[0], m_Position[1], m_Radius/2, m_Radius/2, m_StartAngle+10, m_Degrees-20);
	if(m_RotationVelocity >= 0.f)
	Drawf::FillEllipse(
		m_Position[0] + (m_Radius / 2) * std::cos((m_StartAngle + m_Degrees - 10) * DEG_TO_RAD),
		m_Position[1] + (m_Radius / 2) * std::sin((m_StartAngle + m_Degrees - 10) * DEG_TO_RAD), 3,3);
	else
		Drawf::FillEllipse(
			m_Position[0] + (m_Radius / 2) * std::cos((m_StartAngle + 10) * DEG_TO_RAD),
			m_Position[1] + (m_Radius / 2) * std::sin((m_StartAngle + 10) * DEG_TO_RAD), 3,3);

	ENGINE.SetColor(m_Color);
	Drawf::FillEllipse(m_Position[0], m_Position[1], 5, 5);

#ifdef _DEBUG

	ENGINE.SetColor(RGB(0,255,255));
	Drawf::DrawVector(m_Position[0], m_Position[1], m_StartPlane.e1() * 100, m_StartPlane.e2() * 100);

	ENGINE.SetColor(RGB(255,0,255));
	Drawf::DrawVector(m_Position[0], m_Position[1], m_EndPlane.e1() * 100, m_EndPlane.e2() * 100);
#endif // _DEBUG
}

void RotatorUnit::Update()
{
}

void RotatorUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	if (GAUtils::GetDistance(pProjectile->GetPoint(), m_RotationLine) < m_Radius and
		GAUtils::GetDistance(pProjectile->GetPoint(), m_StartPlane) > 0.f and
		GAUtils::GetDistance(pProjectile->GetPoint(), m_EndPlane) > 0.f)
	{
		pProjectile->SetPossesed(true);
		float angleForPoint = m_RotationVelocity * ENGINE.GetDeltaTime();
		Motor rot = Motor::Rotation(angleForPoint, m_RotationLine);
		pProjectile->Rotate(rot);

		if (GAUtils::GetDistance(pProjectile->GetPoint(), m_EndPlane) < 0.f)
		{
			// First -e0, then the endPlane:
			// because we want to flip the orientation of TranslationLine.
			pProjectile->SetDirection(OneBlade{ -1,0,0,0 } ^ m_EndPlane);
			pProjectile->SetPossesed(false);
		}
	}
	
}

void RotatorUnit::Action1()
{
	m_StartAngle += 45.f;
	if (m_StartAngle >= 360.f) m_StartAngle = 0.f;

	Motor rotation = Motor::Rotation(45, m_RotationLine);

	GAUtils::Transform(m_StartPlane, rotation);
	GAUtils::Transform(m_EndPlane, rotation);
}

void RotatorUnit::Action2()
{
	m_Degrees += 45;
	if (m_Degrees > 180.f)
	{
		m_Degrees = 45;
		if (m_RotationVelocity > 0.f)
			m_EndPlane = -m_StartPlane;
		else
			m_StartPlane = -m_EndPlane;
	}

	Motor rotation{ Motor::Rotation(45, m_RotationLine) };
	if (m_RotationVelocity > 0.f)
		GAUtils::Transform(m_EndPlane, rotation);
	else
		GAUtils::Transform(m_StartPlane, rotation);
}

void RotatorUnit::Action3()
{
	m_RotationVelocity = -m_RotationVelocity;
	
	OneBlade temp = m_StartPlane;

	m_StartPlane = m_EndPlane;
	m_EndPlane = temp;
}

void RotatorUnit::TranslateUnit(const Motor& translation)
{ 
	GAUtils::Transform(m_RotationLine, translation);
	GAUtils::Transform(m_StartPlane, translation);
	GAUtils::Transform(m_EndPlane, translation);

	GAUtils::Transform(m_Position, translation);
}