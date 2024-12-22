#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include <memory>
#include <Engine.h>
#include "Projectile.h"

class Cannon final
{
public:
	Cannon() = default;
	~Cannon() = default;

	Cannon(const Cannon& other) = delete;
	Cannon(Cannon&& other) noexcept = delete;
	Cannon& operator=(const Cannon& other) = delete;
	Cannon& operator=(Cannon&& other) noexcept = delete;

	void Draw() const;
	bool ReadyToFire();
	std::unique_ptr<Projectile> CreateProjectile();
private:
	jela::CircleInt m_BaseShape{60,60,50};
	jela::RectInt m_BarrelShape
	{
		m_BaseShape.center.x,
		static_cast<int>(m_BaseShape.center.y - m_BaseShape.rad + 20),
		80,
		static_cast<int>(m_BaseShape.rad * 2 - 20 * 2)
	};
};

#endif // !CANNON_H