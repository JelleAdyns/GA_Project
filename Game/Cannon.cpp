#include "Cannon.h"
#include "DrawFloatToInt.h"



void Cannon::Draw() const
{
	//ENGINE.SetColor(RGB(255,255,255));
	//Drawf::FillEllipse(m_BaseShape.center, m_BaseShape.radius, m_BaseShape.radius);
	//Drawf::FillRectangle(m_BarrelShape);

	Drawf::DrawTexture(m_rTexture, Rectf{5.f,0.f,Tile::GetSize() * 2,Tile::GetSize() * 2 });
}

bool Cannon::ReadyToFire()
{
	m_Time += ENGINE.GetDeltaTime();
	if (m_Time >= m_FireRate)
	{
		m_Time -= m_FireRate;
		return true;
	}
	
	return false;
}

std::unique_ptr<Projectile> Cannon::CreateProjectile() const
{
	return std::make_unique<Projectile>(static_cast<float>(m_BarrelShape.left + m_BarrelShape.width), static_cast<float>(m_BaseShape.center.y));
}
