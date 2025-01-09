#include "Target.h"
#include "Tile.h"
#include "DrawFloatToInt.h"
#include <algorithm>

Target::Target(float x, float y) :
	m_HitBox{x, y, Tile::GetSize()*2, Tile::GetSize()*2}
{

}
Target::Target(const Point2f& center):
	Target{center.x, center.y}
{
}

void Target::Draw() const
{
	
	Rectf rect{	m_HitBox.Center[0] - m_HitBox.GetWidth() / 2,
				m_HitBox.Center[1] - m_HitBox.GetHeight() / 2,
				m_HitBox.GetWidth(),
				m_HitBox.GetHeight() };

	int rValue = static_cast<int>((m_HitBox.Center[2] / m_KillDepth)*255);
	int gValue = static_cast<int>((1 - (m_HitBox.Center[2] / m_KillDepth))*255);
	
	ENGINE.SetColor(RGB(std::max<int>(std::min<int>(rValue, 255), 0), std::max<int>(std::min<int>(gValue, 255), 0), 0));
	Drawf::FillRectangle(rect);
}

void Target::Update()
{

}

void Target::DealDamage()
{
	Motor tr = Motor::Translation(5, TwoBlade{ 0,0,-1,0,0,0 });
	m_HitBox.Translate(tr);
}

bool Target::IsDead()
{
	return m_HitBox.Center[2] < m_KillDepth;
}

const Box& Target::GetHitBox()
{
	return m_HitBox;
}
