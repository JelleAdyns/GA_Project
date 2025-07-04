#ifndef TARGET_H
#define TARGET_H

#include <Engine.h>
#include "Box.h"
#include "structsf.h"

class Target final
{
public:
	Target(float x, float y);
	Target(const Point2f& center);

	~Target() = default;

	Target(const Target& other) = delete;
	Target(Target&& other) noexcept = delete;
	Target& operator=(const Target& other) = delete;
	Target& operator=(Target&& other) noexcept = delete;

	void Draw() const;
	void Update();
	void DealDamage();
	bool IsDead();
	const Box& GetHitBox();
	constexpr static float GetKillDepth() { return m_KillDepth; }
private:
	constexpr static float m_KillDepth{ -50 };
	constexpr static int m_TextureCols{ 11 };
	int m_CurrCol{ 0 };
	Box m_HitBox;

	const jela::Texture& m_rTexture;
};

#endif TARGET_H