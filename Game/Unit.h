#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include <Engine.h>
#include "Projectile.h"

class Unit
{
public:

	virtual ~Unit() = default;

	Unit(const Unit& other) = delete;
	Unit(Unit&& other) noexcept = delete;
	Unit& operator=(const Unit& other) = delete;
	Unit& operator=(Unit&& other) noexcept = delete;

	virtual void Draw() const {};
	virtual void Update() {};
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) {};
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) {};
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) {};

	virtual void Action1() {};
	virtual void Action2() {};
	virtual void Action3() {};
	virtual void Action4() {};

	virtual void TranslateUnit(const Motor& translation) {};

protected:

	Unit(const Point2f& pos) :
		m_Position{ pos }
	{}

	Point2f m_Position{};
private:
};


#endif // !UNIT_H
