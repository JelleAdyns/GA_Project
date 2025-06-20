#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include <memory>
#include <Engine.h>
#include "Projectile.h"
#include "Tile.h"
#include "structsf.h"

class Cannon final
{
public:
	Cannon(float fireRate):
		m_FireRate{fireRate},
		m_rTexture{jela::ResourceManager::GetInstance().GetTexture(_T("Cannon.png"))}
	{}
	~Cannon() = default;

	Cannon(const Cannon& other) = delete;
	Cannon(Cannon&& other) noexcept = delete;
	Cannon& operator=(const Cannon& other) = delete;
	Cannon& operator=(Cannon&& other) noexcept = delete;

	void Draw() const;
	bool ReadyToFire();
	std::unique_ptr<Projectile> CreateProjectile() const;
private:
	Circlef m_BaseShape{30,Tile::GetSize() + 1,25};
	Rectf m_BarrelShape
	{
		m_BaseShape.center.x,
		m_BaseShape.center.y - m_BaseShape.radius + 10,
		40,
		m_BaseShape.radius * 2 - 10 * 2
	};
	float m_FireRate{};
	float m_Time{};
	jela::Texture& m_rTexture;
};

#endif // !CANNON_H