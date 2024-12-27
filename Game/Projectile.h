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
	
	void SetPossesed(bool posses) { m_Possesed = posses; };
	void SetPoint(const ThreeBlade& pos) { m_Position = pos; };
	ThreeBlade GetPoint() { return m_Position; };

	void Rotate(const Motor& rotationMotor);

private:
	constexpr static int m_Speed{ 100 };
	constexpr static int m_Radius{ 5 };

	bool m_Possesed{ false };

	ThreeBlade m_Position;
	TwoBlade m_TransLine{ 1,0,0,0,0,0 };
	Motor m_Translation{};
	
};

#endif // !PROJECTILE_H