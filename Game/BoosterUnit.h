#ifndef BOOSTERUNIT_H
#define BOOSTERUNIT_H

#include "Unit.h"
#include "Box.h"

class BoosterUnit final: public Unit
{
public:
	BoosterUnit(const Point2f& pos);
	BoosterUnit(float x, float y);

	virtual ~BoosterUnit() = default;

	BoosterUnit(const BoosterUnit& other) = delete;
	BoosterUnit(BoosterUnit&& other) noexcept = delete;
	BoosterUnit& operator=(const BoosterUnit& other) = delete;
	BoosterUnit& operator=(BoosterUnit&& other) noexcept = delete;

	static std::unique_ptr<Unit> CreateUnit(const Point2f& pos);

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) override;
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) const override;
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) const override;

	virtual void Action1() override;
	virtual void Action2() override;
	virtual void Action3() override {};
	virtual void Action4() override {};

	virtual void TranslateUnit(const Motor& translation) override;
private:
	constexpr static float m_Width{ 160 };
	constexpr static float m_Height{ 40 };
	constexpr static COLORREF m_Color{ RGB(234, 124, 25) };

	Box m_Area;
};


#endif // !BOOSTERUNIT_H
