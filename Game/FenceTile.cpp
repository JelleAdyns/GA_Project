#include "FenceTile.h"
#include "DrawFloatToInt.h"
#include "ProjectileOverlapHandler.h"

FenceTile::FenceTile(const Point2f& center):
	Tile{center},
	m_rTexture{jela::ResourceManager::GetInstance().GetTexture(_T("Fence.png"))}
{
	static_assert(m_AcceptanceDepth > Projectile::GetKillDepth());
}

void FenceTile::Draw() const
{
	Rectf rect{ m_Box.Center[0] - m_Box.GetWidth() / 2,
		m_Box.Center[1] - m_Box.GetHeight() / 2,
		m_Box.GetWidth(),
		m_Box.GetHeight() };
	//ENGINE.SetColor(RGB(150, 150, 150), 0.5f);
	//Drawf::FillRectangle(rect);

	Drawf::DrawTexture(m_rTexture, rect);
}

void FenceTile::ActOnProjectile(const std::unique_ptr<Projectile>& pProjectile)
{
	ProjectileOverlapHandler::GetInstance().CheckOverlap(this, m_Box, pProjectile);
}

void FenceTile::BeginOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
	if (pProjectile->GetPoint()[2] < m_AcceptanceDepth)
		pProjectile->SetSpeedMultiplier(0.5f);
	else pProjectile->Kill();
}

void FenceTile::EndOverlap(const std::unique_ptr<Projectile>& pProjectile)
{
	pProjectile->SetSpeedMultiplier(1);
}
