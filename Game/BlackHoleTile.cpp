#include "BlackHoleTile.h"
#include "DrawFloatToInt.h"
#include "ProjectileOverlapHandler.h"

BlackHoleTile::BlackHoleTile(const Point2f& center):
	Tile{center}
{
}

void BlackHoleTile::Draw() const
{
	ENGINE.SetColor(RGB(0, 0, 0));
	Drawf::FillRectangle(
		m_Box.Center[0] - m_Box.GetWidth() / 2,
		m_Box.Center[1] - m_Box.GetHeight() / 2,
		m_Box.GetWidth(),
		m_Box.GetHeight());
}

void BlackHoleTile::ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile)
{

	ProjectileOverlapHandler::GetInstance().CheckOverlap(this, m_Box, pProjectile);
}

void BlackHoleTile::BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) const
{
	pProjectile->AddDirection(TwoBlade{ 0,0,-1,0,0,0 });
}

void BlackHoleTile::EndOverlap(const std::unique_ptr<Projectile>& pProjectile) const
{
	pProjectile->AddDirection(TwoBlade{ 0,0,1,0,0,0 });
}