#ifndef PROJECTILEOVERLAPHANDLER_H
#define PROJECTILEOVERLAPHANDLER_H

#include <map>
#include "Projectile.h"
#include "Tile.h"
#include "Unit.h"

class ProjectileOverlapHandler
{
public:
	static ProjectileOverlapHandler& GetInstance();

	void CheckOverlap(Tile* pTile, const Box& area, const std::unique_ptr<Projectile>& pProjectile);
	void CheckOverlap(Unit* pUnit, const Box& area, const std::unique_ptr<Projectile>& pProjectile);

	void EraseByProjectile(const Projectile* pProjectile);
private:
	ProjectileOverlapHandler() = default;

	std::multimap<Tile*, Projectile*> m_pTiles;
	std::multimap<Unit*, Projectile*> m_pUnits;
};

#endif // !PROJECTILEOVERLAPHANDLER_H