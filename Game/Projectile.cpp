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
		ENGINE.SetColor(RGB(255, 255, 255), (m_Position[2] / 50 + 1));
		Drawf::FillEllipse(std::abs(m_Position[0]), std::abs(m_Position[1]), m_Radius+(m_Position[2] / 50 + 1), m_Radius+(m_Position[2] / 50+1));
	}
}

void Projectile::Update()
{
	if(not m_IsDead)
	{
		if (!m_Possesed)
		{
			m_Translation = Motor::Translation(m_Velocity * ENGINE.GetDeltaTime(), m_TransLine);
			GAUtils::Transform(m_Position, m_Translation);
		}
		m_Possesed = false;

		if (m_Position[2] < -40)
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
		m_TransLine = OneBlade{ -1, 0, 0, 0 } ^ (rotationMotor.Grade2() & m_Position);
	}
}
