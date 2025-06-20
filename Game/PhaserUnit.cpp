#include "PhaserUnit.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"
#include "ProjectileOverlapHandler.h"
#include "FenceTile.h"

PhaserUnit::PhaserUnit(const Point2f& pos) :
	PhaserUnit{ pos.x, pos.y }
{
}

PhaserUnit::PhaserUnit(float x, float y) :
	Unit{ x, y },
	m_Area{ x, y, m_Width, m_Height }
{
}
void PhaserUnit::Draw() const
{
	Unit::Draw();

	std::vector<Point2f> areaCornerPoints{ };
	m_Area.GetCornerPoints(areaCornerPoints);
	ENGINE.SetColor(m_Color, 0.5f);
	Drawf::FillPolygon(areaCornerPoints);
}

void PhaserUnit::Update()
{
}

void PhaserUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile)
{
	ProjectileOverlapHandler::GetInstance().CheckOverlap(this, m_Area, pProjectile);
	if (m_Area.IsPointInside(pProjectile->GetPoint()))
	{
		
		if (pProjectile->GetPoint()[2] > FenceTile::GetAcceptanceDepth())
		{
			ThreeBlade point = pProjectile->GetPoint();
			GAUtils::Transform(point, Motor::Translation(50 * ENGINE.GetDeltaTime(), TwoBlade{ 0,0,-1,0,0,0 }));
			pProjectile->SetPoint(point);
		}
	}
}

void PhaserUnit::BeginOverlap(const std::unique_ptr<Projectile>& pProjectile)
{

}

void PhaserUnit::EndOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
}

void PhaserUnit::Action1()
{
	const TwoBlade rotLine = TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, m_Position[0], m_Position[1], 1);
	m_Area.Rotate(Motor::Rotation(45, rotLine), true);
}

void PhaserUnit::Action2()
{
	const TwoBlade rotLine = TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, m_Position[0], m_Position[1], 1);
	m_Area.Rotate(Motor::Rotation(-45, rotLine), true);
}

void PhaserUnit::TranslateUnit(const Motor& translation)
{
	m_Area.Translate(translation);
	GAUtils::Transform(m_Position, translation);
}
