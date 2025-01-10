#include "BoosterUnit.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"
#include "ProjectileOverlapHandler.h"
#include "BlackHoleTile.h"

BoosterUnit::BoosterUnit(const Point2f& pos):
	BoosterUnit{pos.x, pos.y}
{
}

BoosterUnit::BoosterUnit(float x, float y):
	Unit{ x, y },
	m_Area{x, y, m_Width, m_Height}
{
}

void BoosterUnit::Draw() const
{
	Unit::Draw();

	std::vector<Point2f> areaCornerPoints{ };
	m_Area.GetCornerPoints(areaCornerPoints);
	ENGINE.SetColor(m_Color, 0.5f);
	Drawf::FillPolygon(areaCornerPoints);
}

void BoosterUnit::Update()
{
}

void BoosterUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	ProjectileOverlapHandler::GetInstance().CheckOverlap(this, m_Area, pProjectile);
	if (m_Area.IsPointInside(pProjectile->GetPoint()))
	{
		pProjectile->SetSpeedMultiplier(2);
		ThreeBlade point = pProjectile->GetPoint();
		GAUtils::Transform(point, Motor::Translation(BlackHoleTile::GetPullSpeed()/2 * ENGINE.GetDeltaTime(), TwoBlade{ 0,0,1,0,0,0 }));
		pProjectile->SetPoint(point);
	}
}

void BoosterUnit::BeginOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
	
}

void BoosterUnit::EndOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
	pProjectile->SetSpeedMultiplier(1);
}

void BoosterUnit::Action1()
{
	const TwoBlade rotLine = TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, m_Position[0], m_Position[1], 1);
	Motor rotation = Motor::Rotation(45, rotLine);
	m_Area.Rotate(rotation, true);
}

void BoosterUnit::Action2()
{
}

void BoosterUnit::TranslateUnit(const Motor& translation)
{
	m_Area.Translate(translation);
	GAUtils::Transform(m_Position, translation);
}
