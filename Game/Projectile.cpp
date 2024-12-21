#include "Projectile.h"
#include "DrawFloatToInt.h"


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
		//Motor rotation = Motor::Rotation(45, TwoBlade{ 0,0,0,0,1,0 });
		//auto newPlane = (rotation * OneBlade{ 0,1,1,0 } * ~rotation);

		//m_TransLine.Normalize();

		m_Translation = Motor::Translation(m_Speed * ENGINE.GetDeltaTime(), m_TransLine);
		m_Position = ((m_Translation * m_Position * ~m_Translation)).Normalized().Grade3();

		std::for_each(m_TransLine.begin(), m_TransLine.end(), [&](float& data) {
			data = std::round(data); });
	}
	m_Possesed = false;
}

void Projectile::Rotate(const Motor& rotationMotor)
{
	m_Position = (rotationMotor * m_Position * ~rotationMotor).Normalized().Grade3();

	// Join rotationLine and projectile position, which create a plane.
	// Intersect that plane with -e0 to get the current translation vanishing line.
	m_TransLine = (rotationMotor.Grade2() & m_Position) ^ OneBlade{ -1, 0, 0, 0 };


	//m_TransLine = (rotationMotor * m_TransLine * ~rotationMotor).Grade2();
	//m_TransLine = OneBlade{ -1,0,0,0 } ^ m_TransPlane;
}
