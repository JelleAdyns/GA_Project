#include "Tile.h"
#include "DrawFloatToInt.h"
#include <Engine.h>

Tile::Tile(const Point2f& center):
	m_Box{center, m_Size, m_Size}
{
}

void Tile::Draw() const
{
	 
	Rectf rect{	m_Box.Center[0] - m_Box.GetWidth() / 2,
				m_Box.Center[1] - m_Box.GetHeight() / 2,
				m_Box.GetWidth(),
				m_Box.GetHeight()  };

	ENGINE.SetColor(RGB(180, 0, 0));
	Drawf::FillRectangle(rect);
	ENGINE.SetColor(RGB(0, 0, 0));
	Drawf::DrawRectangle(rect);
}

void Tile::ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile)
{
	if (m_Box.IsPointInside(pProjectile->GetPoint(), Projectile::GetRadius()))
	{
		pProjectile->Kill();
	}
}
