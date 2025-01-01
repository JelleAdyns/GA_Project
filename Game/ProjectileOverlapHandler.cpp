#include "ProjectileOverlapHandler.h"
#include <algorithm>

ProjectileOverlapHandler& ProjectileOverlapHandler::GetInstance()
{
    static ProjectileOverlapHandler handler{};
    return handler;
}

void ProjectileOverlapHandler::CheckOverlap(Tile* pTile, const Box& area, const std::unique_ptr<Projectile>& pProjectile)
{
    if ((not pProjectile) or pProjectile->IsDead()) return;
    if (not pTile) return;

    //If no pTile key in map yet
    if (not m_pTiles.contains(pTile) )
    {
        if (area.IsPointInside(pProjectile->GetPoint()))
        {
            m_pTiles.insert({ pTile, pProjectile.get() });
            pTile->BeginOverlap(pProjectile);
        }
        return;
    }
   
    auto range = m_pTiles.equal_range(pTile);
       
    bool projectileAlreadyInMap = std::any_of(range.first, range.second,
        [&](const std::pair<Tile*, Projectile*>& pair)
        {
            return (pair.second == pProjectile.get());
        });

    // else if pTile is already in map and pProjectile is not linked yet
    if (not projectileAlreadyInMap)
    {
        if (area.IsPointInside(pProjectile->GetPoint()))
        {
            m_pTiles.insert({ pTile, pProjectile.get() });
            pTile->BeginOverlap(pProjectile);
        }
        return;
    }

    // else if pTile is already in map and pProjectile is already linked
    if (not area.IsPointInside(pProjectile->GetPoint()))
    {
        pTile->EndOverlap(pProjectile);
        std::erase_if(m_pTiles, [&](const std::pair<Tile*, Projectile*>& pair)
            {
                return (pair.first == pTile) && (pair.second == pProjectile.get());
            }
        );
    } 

}

void ProjectileOverlapHandler::CheckOverlap(Unit* pUnit, const Box& area, const std::unique_ptr<Projectile>& pProjectile)
{
    if ((not pProjectile) or pProjectile->IsDead()) return;
    if (not pUnit) return;

    //If no pUnit key in map yet
    if (not m_pUnits.contains(pUnit))
    {
        if (area.IsPointInside(pProjectile->GetPoint()))
        {
            m_pUnits.insert({ pUnit, pProjectile.get() });
            pUnit->BeginOverlap(pProjectile);
        }
        return;
    }

    auto range = m_pUnits.equal_range(pUnit);

    bool projectileAlreadyInMap = std::any_of(range.first, range.second,
        [&](const std::pair<Unit*, Projectile*>& pair)
        {
            return (pair.second == pProjectile.get());
        });

    // else if pUnit is already in map and pProjectile is not linked yet
    if (not projectileAlreadyInMap)
    {
        if (area.IsPointInside(pProjectile->GetPoint()))
        {
            m_pUnits.insert({ pUnit, pProjectile.get() });
            pUnit->BeginOverlap(pProjectile);
        }
        return;
    }

    // else if pUnit is already in map and pProjectile is already linked
    if (not area.IsPointInside(pProjectile->GetPoint()))
    {
        pUnit->EndOverlap(pProjectile);
        std::erase_if(m_pUnits, [&](const std::pair<Unit*, Projectile*>& pair)
            {
                return (pair.first == pUnit) && (pair.second == pProjectile.get());
            }
        );
    }

    
}

void ProjectileOverlapHandler::EraseByProjectile(const Projectile* pProjectile)
{
    std::erase_if(m_pTiles, [&](const std::pair<Tile*, Projectile*>& pair)
        {
            return (pair.second == pProjectile);
        }
    );
    std::erase_if(m_pUnits, [&](const std::pair<Unit*, Projectile*>& pair)
        {
            return (pair.second == pProjectile);
        }
    );
}
