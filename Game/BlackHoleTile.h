#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "structsf.h"
#include "Box.h"
#include "Tile.h"

class BlackHole final : public Tile
{
public:
	BlackHole(const Point2f& center);
	~BlackHole() = default;

	BlackHole(const BlackHole& other) = delete;
	BlackHole(BlackHole&& other) noexcept = delete;
	BlackHole& operator=(const BlackHole& other) = delete;
	BlackHole& operator=(BlackHole&& other) noexcept = delete;

	void Draw() const;

private:
	
};

#endif // !BLACKHOLE_H
