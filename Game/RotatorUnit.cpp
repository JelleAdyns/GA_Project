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

std::unique_ptr<Unit> RotatorUnit::CreateUnit(const Point2f& pos)
{
	return std::make_unique<RotatorUnit>(pos);
	//return std::make_unique<RotatorUnit>(ENGINE.GetWindowRect().width/2.f, ENGINE.GetWindowRect().height / 2.f-200);
}

void RotatorUnit::Draw() const
{
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

	ENGINE.SetColor(RGB(100, 140, 25));
	Drawf::FillEllipse(m_Position.x, m_Position.y, 10, 10);
}

void RotatorUnit::Update()
{
}

void RotatorUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	//float projectileAngle = CalculateProjectileAngle(pProjectile);

	if (GAUtils::GetDistance(pProjectile->GetPoint(), m_RotationLine) < m_Radius and
		GAUtils::GetDistance(pProjectile->GetPoint(), m_StartPlane) > 0.f and
		GAUtils::GetDistance(pProjectile->GetPoint(), m_EndPlane) > 0.f)
	{
		pProjectile->SetPossesed(true);
		float angleForPoint = m_RotationVelocity * ENGINE.GetDeltaTime();
		Motor rot = Motor::Rotation(angleForPoint, m_RotationLine);
		pProjectile->Rotate(rot);
	}
	
}

void RotatorUnit::Action1()
{
	m_StartAngle += 90.f;
	if (m_StartAngle >= 360.f) m_StartAngle = 0.f;

	GAUtils::RotatePlane(m_StartPlane, 90, m_RotationLine);
	GAUtils::RotatePlane(m_EndPlane, 90, m_RotationLine);
	//MultiVector rot{};
	//rot = (-sin(90 * DEG_TO_RAD / 2) * m_RotationLine.Normalized());
	//rot[0] = cos(90 * DEG_TO_RAD / 2);
	//
	//Motor rotat = Motor::Rotation(90, m_RotationLine);
	//m_StartPlane = (rotat * m_StartPlane * ~rotat).Grade1();
	//m_EndPlane = (rotat * m_EndPlane * ~rotat).Grade1();
}

void RotatorUnit::Action2()
{
	if (m_Degrees == 180.f)
	{
		m_Degrees = 90;
		GAUtils::RotatePlane(m_EndPlane, -90, m_RotationLine);
		//MultiVector rot{};
		//rot = (-sin(-90 * DEG_TO_RAD / 2) * m_RotationLine.Normalized());
		//rot[0] = cos(-90 * DEG_TO_RAD / 2);
		////Motor rot = Motor::Rotation(-90, m_RotationLine);
		//m_EndPlane = (rot * m_EndPlane.Normalized() * ~rot).Normalized().Grade1();
	}
	else
	{
		m_Degrees = 180;
		GAUtils::RotatePlane(m_EndPlane, 90, m_RotationLine);
		//MultiVector rot{};
		//rot = (-sin(-90 * DEG_TO_RAD / 2) * m_RotationLine.Normalized());
		//rot[0] = cos(-90 * DEG_TO_RAD / 2);
		//Motor rot = Motor::Rotation(90, m_RotationLine);
		//m_EndPlane = (rot * m_EndPlane.Normalized() * ~rot).Normalized().Grade1();
	}
	//m_Degrees = (m_Degrees == 180.f ? 90.f : 180.f);
}

void RotatorUnit::Action3()
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
