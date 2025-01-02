#include "BoosterUnit.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"
#include "ProjectileOverlapHandler.h"

BoosterUnit::BoosterUnit(const Point2f& pos):
	BoosterUnit{pos.x, pos.y}
{
}

BoosterUnit::BoosterUnit(float x, float y):
	Unit{ Point2f{x, y} },
	m_Area{x, y, m_Width, m_Height}
{
}

std::unique_ptr<Unit> BoosterUnit::CreateUnit(const Point2f& pos)
{
	return std::make_unique<BoosterUnit>(pos);
}

void BoosterUnit::Draw() const
{
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
}

void BoosterUnit::BeginOverlap(const std::unique_ptr<Projectile>& pProjectile) const
{
	pProjectile->SetSpeedMultiplier(2);
	pProjectile->AddDirection(TwoBlade{ 0,0,1,0,0,0 });
}

void BoosterUnit::EndOverlap(const std::unique_ptr<Projectile>& pProjectile) const
{
	pProjectile->SetSpeedMultiplier(1);
}

void BoosterUnit::Action1()
{
	const TwoBlade rotLine = TwoBlade::LineFromPoints(m_Position.x, m_Position.y, 0, m_Position.x, m_Position.y, 1);
	Motor rotation = Motor::Rotation(90, rotLine);
	m_Area.Rotate(rotation, true);
}

void BoosterUnit::Action2()
{
}

void BoosterUnit::TranslateUnit(const Motor& translation)
{
	m_Area.Translate(translation);

	ThreeBlade newPoint{ m_Position.x, m_Position.y,0 };
	GAUtils::Transform(newPoint, translation);
	m_Position = Point2f{ newPoint[0], newPoint[1] };
}
