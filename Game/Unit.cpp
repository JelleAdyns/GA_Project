#include "Unit.h"
#include "DrawFloatToInt.h"

Unit::Unit(const Point2f& pos):
	m_Position{pos}
{
}

void Unit::Draw() const
{

}

void Unit::Update()
{
	
}

void Unit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	//Check if overlapping here

	//if overlapping, act on the projectile
}
