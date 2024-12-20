#ifndef ROTATORUNIT_H
#define ROTATORUNIT_H

#include <Engine.h>
#include "Unit.h"

class RotatorUnit final : public Unit
{
public:
	RotatorUnit(float x, float y);
	static std::unique_ptr<Unit> CreateUnit();

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) const override;

private:
	TwoBlade m_RotationLine;
	float m_Degrees{ 180 };
	ThreeBlade m_TempPoint;
};

#endif // !ROTATORUNIT_H
