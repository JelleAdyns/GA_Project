#ifndef UNIT_H
#define UNIT_H

#include <memory>
#include <Engine.h>
#include "Projectile.h"

class Unit
{
public:
	Unit(const Point2f& pos);
	virtual void Draw() const;
	virtual void Update();
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) const;
protected:
	Point2f m_Position{};
private:
};


#endif // !UNIT_H
