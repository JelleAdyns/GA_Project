#include "RotatorUnit.h"
#include "FlyFish.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"

RotatorUnit::RotatorUnit(const Point2f& pos) :
	RotatorUnit{ pos.x, pos.y }
{

}
RotatorUnit::RotatorUnit(float x, float y):
	Unit{ Point2f{x, y}},
	m_RotationLine{ TwoBlade::LineFromPoints(x,y,0, x,y,1) }
	//m_SeperationPlane{ -y,0,1,0 }
{
}

std::unique_ptr<RotatorUnit> RotatorUnit::CreateUnit(const Point2f& pos)
{
	return std::make_unique<RotatorUnit>(pos);
	//return std::make_unique<RotatorUnit>(ENGINE.GetWindowRect().width/2.f, ENGINE.GetWindowRect().height / 2.f-200);
}

void RotatorUnit::Draw() const
{
	Unit::Draw();
	ENGINE.SetColor(RGB(255,255,255), 0.5f);
	Drawf::FillArc(m_Position.x, m_Position.y, m_Radius, m_Radius, m_StartAngle, m_Degrees);
	ENGINE.SetColor(RGB(255,0,0), 0.5f);
	Drawf::DrawArc(m_Position.x, m_Position.y, m_Radius/2, m_Radius/2, m_StartAngle+10, m_Degrees-20);
	if(m_RotationVelocity >= 0.f)
	Drawf::FillEllipse(
		m_Position.x + (m_Radius / 2) * std::cos((m_StartAngle + m_Degrees - 10) * DEG_TO_RAD),
		m_Position.y + (m_Radius / 2) * std::sin((m_StartAngle + m_Degrees - 10) * DEG_TO_RAD), 5, 5);
	else
		Drawf::FillEllipse(
			m_Position.x + (m_Radius / 2) * std::cos((m_StartAngle + 10) * DEG_TO_RAD),
			m_Position.y + (m_Radius / 2) * std::sin((m_StartAngle + 10) * DEG_TO_RAD), 5, 5);
}

void RotatorUnit::Update()
{
}

void RotatorUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	if (ENGINE.IsKeyPressed('9')) return;

	float projectileAngle = CalculateProjectileAngle(pProjectile);

	if (GAUtils::GetDistance(pProjectile->GetPoint(), m_RotationLine) < m_Radius and
		projectileAngle > m_StartAngle and projectileAngle < m_StartAngle + m_Degrees)
	{
		pProjectile->SetPossesed(true);
		float angleForPoint = m_RotationVelocity * ENGINE.GetDeltaTime();
		Motor rot = Motor::Rotation(angleForPoint, m_RotationLine.Normalized());
		pProjectile->Rotate(rot);
		//pProjectile->SetPoint((rot * pProjectile->GetPoint() * ~rot).Normalized().Grade3());
	}
}

void RotatorUnit::AddStartAngle()
{
	m_StartAngle += 90.f;
	if (m_StartAngle >= 360.f) m_StartAngle = 0.f;
	//Motor rot = Motor::Rotation(m_StartAngle, m_RotationLine.Normalized());
	//m_SeperationPlane = (rot * m_SeperationPlane * ~rot).Normalized().Grade1();
}

void RotatorUnit::SwitchDegrees()
{
	m_Degrees = (m_Degrees == 180.f ? 90.f : 180.f);
}

void RotatorUnit::ToggleDirection()
{
	m_RotationVelocity = -m_RotationVelocity;
}

float RotatorUnit::CalculateProjectileAngle(std::unique_ptr<Projectile>& pProjectile)
{
	auto pointOnLine = GAUtils::Project(pProjectile->GetPoint(), m_RotationLine);
	auto projectileToOrigin = (pProjectile->GetPoint() - pointOnLine);

	float angle = std::atan2(projectileToOrigin[1], projectileToOrigin[0]) / DEG_TO_RAD;
	if (angle < 0.f) angle = 180 + (180 + angle);

	return angle;
}
