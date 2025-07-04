#ifndef TILE_H
#define TILE_H

#include <Engine.h>
#include "structsf.h"
#include "Box.h"
#include "Projectile.h"

class Tile
{
public:
	Tile(const Point2f& center);
	~Tile() = default;

	Tile(const Tile& other) = delete;
	Tile(Tile&& other) noexcept = delete;
	Tile& operator=(const Tile& other) = delete;
	Tile& operator=(Tile&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile);
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) {};
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) {};

	bool IsPointInside(const ThreeBlade& point) const { return m_Box.IsPointInside(point); };
	constexpr static float GetSize() { return m_Size; }

protected:
	Box m_Box;

private:
	jela::Texture& m_rTileTexture;
	constexpr static float m_Size{ 32 };
};

#endif // !TILE_H
