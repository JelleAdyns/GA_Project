#ifndef ROTATORUNIT_H
#define ROTATORUNIT_H

#include <Engine.h>
#include "Unit.h"
#include "structsf.h"

class RotatorUnit final : public Unit
{
public:
	RotatorUnit(const Point2f& pos);
	RotatorUnit(float x, float y);

	virtual ~RotatorUnit() = default;

	RotatorUnit(const RotatorUnit& other) = delete;
	RotatorUnit(RotatorUnit&& other) noexcept = delete;
	RotatorUnit& operator=(const RotatorUnit& other) = delete;
	RotatorUnit& operator=(RotatorUnit&& other) noexcept = delete;

	static std::unique_ptr<Unit> CreateUnit(const Point2f& pos);

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) override;
	
	virtual void Action1() override;
	virtual void Action2() override;
	virtual void Action3() override;
	virtual void Action4() override {};

private:

	constexpr static float m_Radius{ 50 };

	float m_Degrees{ 180 };
	float m_StartAngle{ 0 };
	float m_RotationVelocity{ 60 };
	TwoBlade m_RotationLine;
	OneBlade m_StartPlane{ -m_Position.y,0,1,0 };
	OneBlade m_EndPlane{ -m_Position.y,0,1,0 };
};

#endif // !ROTATORUNIT_H
