#ifndef FENCETILE_H
#define FENCETILE_H

#include "Box.h"
#include "Tile.h"

class FenceTile final : public Tile
{
public:
	FenceTile(const Point2f& center);
	~FenceTile() = default;

	FenceTile(const FenceTile& other) = delete;
	FenceTile(FenceTile&& other) noexcept = delete;
	FenceTile& operator=(const FenceTile& other) = delete;
	FenceTile& operator=(FenceTile&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile) override;
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) override;
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) override;

	constexpr static float GetAcceptanceDepth() { return m_AcceptanceDepth; }
private:
	constexpr static float m_AcceptanceDepth{ -10 };
	jela::Texture& m_rTexture;
};

#endif // !FENCETILE_H