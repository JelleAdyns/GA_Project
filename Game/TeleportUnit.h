#ifndef TELEPORTUNIT_H
#define TELEPORTUNIT_H

#include <Engine.h>
#include "Unit.h"
#include "Box.h"
#include "structsf.h"

class TeleportUnit final : public Unit
{
public:
	TeleportUnit(const Point2f& pos);
	TeleportUnit(float x, float y);

	virtual ~TeleportUnit() = default;

	TeleportUnit(const TeleportUnit& other) = delete;
	TeleportUnit(TeleportUnit&& other) noexcept = delete;
	TeleportUnit& operator=(const TeleportUnit& other) = delete;
	TeleportUnit& operator=(TeleportUnit&& other) noexcept = delete;

	static std::unique_ptr<Unit> CreateUnit(const Point2f& pos);

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) override;

	virtual void Action1() override;
	virtual void Action2() override {};
	virtual void Action3() override {};
	virtual void Action4() override {};

	virtual void TranslateUnit(const Motor& translation) override;
private:
	constexpr static float m_Width{25};
	constexpr static float m_Height{35};
	constexpr static COLORREF m_Color{RGB(245, 123, 145)};

	OneBlade m_ReflectPlane{m_Position.y,0,-1,0};
	Box m_ActivationBox{m_Position.x, m_Position.y - m_Height, m_Width, m_Height };
};

#endif // !TELEPORTUNIT_H
