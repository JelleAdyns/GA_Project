#include "Projectile.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"


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
	ENGINE.SetColor(RGB(255,255,255));
	Drawf::FillEllipse(m_Position[0], m_Position[1], m_Radius, m_Radius);
}

void Projectile::Update()
{
	if (!m_Possesed)
	{
			m_Translation = Motor::Translation(m_Velocity * ENGINE.GetDeltaTime(), m_TransLine);
			GAUtils::Transform(m_Position, m_Translation);
	}
	m_Possesed = false;
}

void Projectile::Rotate(const Motor& rotationMotor)
{
	m_Position = (rotationMotor * m_Position * ~rotationMotor).Normalized().Grade3();
	{
		GAUtils::Transform(m_Position, rotationMotor);
		m_TransLine = OneBlade{ -1, 0, 0, 0 } ^ (rotationMotor.Grade2() & m_Position);
	}
}
