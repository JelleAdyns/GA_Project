#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include <Engine.h>
#include "Projectile.h"

class Unit
{
public:
	Unit(const Point2f& pos);

	virtual ~Unit() = default;

	Unit(const Unit& other) = delete;
	Unit(Unit&& other) noexcept = delete;
	Unit& operator=(const Unit& other) = delete;
	Unit& operator=(Unit&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void Update();
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile);
protected:
	Point2f m_Position{};
private:
};


#endif // !UNIT_H
