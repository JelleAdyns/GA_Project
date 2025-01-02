#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Engine.h>
#include "FlyFish.h"
#include "structsf.h"

class Projectile final
{
public:
	Projectile(float xCenter, float yCenter);
	Projectile(const Point2f& pos);

	~Projectile() = default;

	Projectile(const Projectile& other) = delete;
	Projectile(Projectile&& other) noexcept = delete;
	Projectile& operator=(const Projectile& other) = delete;
	Projectile& operator=(Projectile&& other) noexcept = delete;

	void Draw() const;
	void Update();
	
	void AddDirection(const TwoBlade& transLine) { m_TransLine += transLine; }
	void SetDirection(const TwoBlade& transLine) { m_TransLine = transLine; }
	void SetPossesed(bool posses) { m_Possesed = posses; }
	void SetPoint(const ThreeBlade& pos) { m_Position = pos; }
	void SetSpeedMultiplier(float speedMultiplier) { m_SpeedMultiplier = speedMultiplier; }
	void Kill();

	ThreeBlade GetPoint() const { return m_Position; } 
	bool IsDead() const { return m_IsDead; } 

	void Rotate(const Motor& rotationMotor);

	constexpr static float GetDefaultSpeed() { return m_DefaultSpeed; }
	constexpr static float GetKillDepth() { return m_KillDepth; }

private:
	constexpr static int m_DefaultSpeed{ 100 };
	constexpr static int m_Radius{ 5 };
	constexpr static float m_KillDepth{ -20 };

	float m_SpeedMultiplier{ 1.f };
	float m_Speed{ m_DefaultSpeed };
	bool m_Possesed{ false };
	bool m_IsDead{ false };

	ThreeBlade m_Position;
	TwoBlade m_TransLine{ 1,0,0,0,0,0 };
	Motor m_Translation{};
	
};

#endif // !PROJECTILE_H