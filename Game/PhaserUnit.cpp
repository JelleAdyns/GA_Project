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
	Unit{ Point2f{x, y} },
	m_Area{ x, y, m_Width, m_Height }
{
}

std::unique_ptr<Unit> PhaserUnit::CreateUnit(const Point2f& pos)
{
	return std::make_unique<PhaserUnit>(pos);
}

void PhaserUnit::Draw() const
{
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
		if (pProjectile->GetPoint()[2] < FenceTile::GetAcceptanceDepth())
		{
			auto currentDir = pProjectile->GetTransLine();
			currentDir[2] = 0;
			pProjectile->SetDirection(currentDir);
		}
	}
}

void PhaserUnit::BeginOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
	m_TransDownwards = TwoBlade{ 0,0,-1,0,0,0 } + pProjectile->GetTransLine();
	pProjectile->AddDirection(m_TransDownwards);
}

void PhaserUnit::EndOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
	pProjectile->AddDirection(-m_TransDownwards);
}

void PhaserUnit::Action1()
{
	const TwoBlade rotLine = TwoBlade::LineFromPoints(m_Position.x, m_Position.y, 0, m_Position.x, m_Position.y, 1);
	Motor rotation = Motor::Rotation(90, rotLine);
	m_Area.Rotate(rotation, true);
}

void PhaserUnit::Action2()
{
}

void PhaserUnit::TranslateUnit(const Motor& translation)
{
	m_Area.Translate(translation);

	ThreeBlade newPoint{ m_Position.x, m_Position.y,0 };
	GAUtils::Transform(newPoint, translation);
	m_Position = Point2f{ newPoint[0], newPoint[1] };
}
