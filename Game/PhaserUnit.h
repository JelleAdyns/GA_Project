#ifndef PHASERUNIT_H
#define PHASERUNIT_H

#include "Unit.h"
#include "Box.h"

class PhaserUnit final : public Unit
{
public:
	PhaserUnit(const Point2f& pos);
	PhaserUnit(float x, float y);

	virtual ~PhaserUnit() = default;

	PhaserUnit(const PhaserUnit& other) = delete;
	PhaserUnit(PhaserUnit&& other) noexcept = delete;
	PhaserUnit& operator=(const PhaserUnit& other) = delete;
	PhaserUnit& operator=(PhaserUnit&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) override;
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) override;
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) override;

	virtual void Action1() override;
	virtual void Action2() override;
	virtual void Action3() override {};
	virtual void Action4() override {};

	virtual void TranslateUnit(const Motor& translation) override;

private:
	constexpr static float m_Width{ 160 };
	constexpr static float m_Height{ 40 };
	constexpr static COLORREF m_Color{ RGB(23, 156, 225) };

	TwoBlade m_TransDownwards{ };

	Box m_Area;
};


#endif // !PHASERUNIT_H
