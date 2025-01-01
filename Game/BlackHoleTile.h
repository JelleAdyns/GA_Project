#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "Box.h"
#include "Tile.h"

class BlackHoleTile final : public Tile
{
public:
	BlackHoleTile(const Point2f& center);
	~BlackHoleTile() = default;

	BlackHoleTile(const BlackHoleTile& other) = delete;
	BlackHoleTile(BlackHoleTile&& other) noexcept = delete;
	BlackHoleTile& operator=(const BlackHoleTile& other) = delete;
	BlackHoleTile& operator=(BlackHoleTile&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile) override;
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) const override;
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) const override;

	void Translate(TwoBlade tr);

private:
	
	Motor m_PullTranslation{};
};

#endif // !BLACKHOLE_H
