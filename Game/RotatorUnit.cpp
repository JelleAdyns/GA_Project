#include "RotatorUnit.h"
#include "FlyFish.h"
#include "DrawFloatToInt.h"
#include "GAUtils.h"

RotatorUnit::RotatorUnit(float x, float y):
	Unit{ Point2f{x, y}},
	//m_RotationLine{ x,y,0,0,0,1 },
	m_RotationLine{ TwoBlade::LineFromPoints(x,y,0, x,y,-1) },
	m_TempPoint{x - 75.f, y, 0}
{
}

std::unique_ptr<Unit> RotatorUnit::CreateUnit()
{
	return std::make_unique<RotatorUnit>(static_cast<float>(rand() % 1200), static_cast<float>(rand() % 700));
	//return std::make_unique<RotatorUnit>(ENGINE.GetWindowRect().width/2.f, ENGINE.GetWindowRect().height / 2.f-200);
}

void RotatorUnit::Draw() const
{
	Unit::Draw();
	ENGINE.SetColor(RGB(255,255,255), 0.5f);
	//ENGINE.DrawEllipse((int)m_TempPoint[0], (int)m_TempPoint[1], 20, 20);
	//Drawf::FillEllipse(m_TempPoint[0], m_TempPoint[1], 20, 20);
	//Drawf::DrawLine(m_RotationLine[0], m_RotationLine[1], m_TempPoint[0], m_TempPoint[1]);
	Drawf::FillArc(m_Position.x, m_Position.y, 100, 100, 0, m_Degrees);
}

void RotatorUnit::Update()
{
	float angleForPoint = 60 * ENGINE.GetDeltaTime();
	Motor rot = Motor::Rotation(angleForPoint, m_RotationLine);
	m_TempPoint = ((rot * m_TempPoint * ~rot)).Grade3();
}

void RotatorUnit::ActOnProjectile(std::unique_ptr<Projectile>& pProjectile) const
{
	if (ENGINE.IsKeyPressed('9')) return;

	if (GAUtils::GetDistance(pProjectile->GetPoint(), m_RotationLine) < 100)
	{
		pProjectile->SetPossesed(true);
		float angleForPoint = -60 * ENGINE.GetDeltaTime();
		Motor rot = Motor::Rotation(angleForPoint, m_RotationLine.Normalized());
		pProjectile->Rotate(rot);
		//pProjectile->SetPoint((rot * pProjectile->GetPoint() * ~rot).Normalized().Grade3());
	}
}
