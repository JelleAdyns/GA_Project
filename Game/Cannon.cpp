#include "Cannon.h"
#include "DrawFloatToInt.h"



void Cannon::Draw() const
{
	ENGINE.SetColor(RGB(255,255,255));
	Drawf::FillEllipse(m_BaseShape.center, m_BaseShape.radius, m_BaseShape.radius);
	Drawf::FillRectangle(m_BarrelShape);

}

bool Cannon::ReadyToFire()
{
	static float fireRate{ 1.f };
	static float time{0.f};
	time += ENGINE.GetDeltaTime();
	if (time >= fireRate)
	{
		time -= fireRate;
		return true;
	}

	return false;
}

std::unique_ptr<Projectile> Cannon::CreateProjectile()
{
	return std::make_unique<Projectile>(static_cast<float>(m_BarrelShape.left + m_BarrelShape.width), static_cast<float>(m_BaseShape.center.y));
}
