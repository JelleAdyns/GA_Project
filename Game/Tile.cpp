#include "Tile.h"
#include "DrawFloatToInt.h"

Tile::Tile(const Point2f& center):
	m_Box{center, m_Size, m_Size},
	m_rTileTexture{ jela::ResourceManager::GetInstance().GetTexture(_T("Tile.png")) }
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

	Drawf::DrawTexture(m_rTileTexture, rect);
}

void Tile::ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile)
{
	if (m_Box.IsPointInside(pProjectile->GetPoint(), Projectile::GetRadius()))
	{
		pProjectile->Kill();
	}
}
