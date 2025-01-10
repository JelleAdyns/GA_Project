#include "Projectile.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"
#include "ProjectileOverlapHandler.h"


Projectile::Projectile(float xCenter, float yCenter) :
	m_Position{ xCenter, yCenter, 0 }
{
}

Projectile::Projectile(const Point2f& pos):
	Projectile{pos.x, pos.y}
{
}

void Projectile::Draw() const
{
	if(not m_IsDead)
	{
		float depthValue = (m_Position[2] / std::abs(m_KillDepth + 1) + 1);
		ENGINE.SetColor(RGB(255, 255, 255), depthValue);
		Drawf::FillEllipse(std::abs(m_Position[0]), std::abs(m_Position[1]), m_Radius+depthValue, m_Radius+depthValue);
	}
}

void Projectile::Update()
{
	if(not m_IsDead)
	{

		if (std::abs(m_Position[2]) > 0.0001f and 
			(not ProjectileOverlapHandler::GetInstance().IsOverlapping(this)))
		{	
			m_Position = GAUtils::Project(m_Position, OneBlade{ 0,0,0,1 });
		}
		if (!m_Possesed)
		{
			if(std::abs(m_TransLine[2]) > 0.001f)
			{
				auto origin = ThreeBlade{ 0,0,0 };
				auto defaultPlane = TwoBlade{ m_TransLine[0],m_TransLine[1],0,0,0,0 } &origin;
				auto currentPlane = m_TransLine & origin;

				m_Speed = m_DefaultSpeed / std::abs(std::cos(GAUtils::GetAngle(defaultPlane, currentPlane)));
			}
			m_Translation = Motor::Translation(m_Speed * m_SpeedMultiplier * ENGINE.GetDeltaTime(), m_TransLine);
			GAUtils::Transform(m_Position, m_Translation);
		}
		m_Possesed = false;

		if (m_Position[2] < m_KillDepth)
			Kill();
		
	}
}

void Projectile::Kill()
{
	ProjectileOverlapHandler::GetInstance().EraseByProjectile(this);
	m_IsDead = true;
}
void Projectile::Rotate(const Motor& rotationMotor)
{
	if (not m_IsDead)
	{
		GAUtils::Transform(m_Position, rotationMotor);
		if (not ProjectileOverlapHandler::GetInstance().IsOverlapping(this))
			m_TransLine = OneBlade{ -1, 0, 0, 0 } ^ (rotationMotor.Grade2() & m_Position);
	}
}
