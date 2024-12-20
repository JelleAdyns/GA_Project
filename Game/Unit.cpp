#include "Unit.h"
#include "DrawFloatToInt.h"

Unit::Unit(const Point2f& pos):
	m_Position{pos}
{
}

void Unit::Draw() const
{
	ENGINE.SetColor(RGB( 100,140,25));
	Drawf::FillEllipse(m_Position.x, m_Position.y, 10, 10);
	//Drawf::FillEllipse(m_Position.x, 10, 10);
}

void Unit::Update()
{
	
}

void Unit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) const
{
	//Check if overlapping here

	//if overlapping, act on the projectile
}
