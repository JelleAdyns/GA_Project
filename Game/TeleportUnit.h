#ifndef TELEPORTUNIT_H
#define TELEPORTUNIT_H

#include <Engine.h>
#include "Unit.h"
#include "Tile.h"
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

	virtual void Draw() const override;
	virtual void Update() override;
	virtual void ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) override;
	virtual void BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) override {};
	virtual void EndOverlap(const std::unique_ptr<Projectile>& pProjectile) override {};

	virtual void Action1() override;
	virtual void Action2() override;
	virtual void Action3() override;
	virtual void Action4() override;

	virtual void TranslateUnit(const Motor& translation) override;
private:
	void Rotate(float degrees);
	void ApplyOffset(float dist);

	constexpr static float m_Width{Tile::GetSize()};
	constexpr static float m_Height{Tile::GetSize()*1.5f};
	constexpr static float m_MaxDistFromPlane{Tile::GetSize()*2};
	constexpr static float m_MinDistFromPlane{m_Height/2};
	constexpr static float m_OffsetStep{10};
	constexpr static float m_DegreesStep{45};
	constexpr static COLORREF m_Color{RGB(245, 123, 145)};

	OneBlade m_ReflectPlane{m_Position[1],0,-1,0};
	Box m_ActivationBox{ m_Position[0], m_Position[1] - (m_Height / 2 + m_OffsetStep), m_Width, m_Height};
	Box m_DestinationBox{ m_ActivationBox };
};

#endif // !TELEPORTUNIT_H
