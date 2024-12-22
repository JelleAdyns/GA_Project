#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include <Engine.h>
#include "Projectile.h"

class Unit
{
public:
	Unit(const Point2f& pos) :
		m_Position{ pos }
	{}

	virtual ~Unit() = default;

	Unit(const Unit& other) = delete;
	Unit(Unit&& other) noexcept = delete;
	Unit& operator=(const Unit& other) = delete;
	Unit& operator=(Unit&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update() = 0;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) = 0;

	virtual void Action1() = 0;
	virtual void Action2() = 0;
	virtual void Action3() = 0;
	virtual void Action4() = 0;


protected:
	Point2f m_Position{};
private:
};


#endif // !UNIT_H
