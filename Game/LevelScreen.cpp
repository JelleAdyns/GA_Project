#include "LevelScreen.h"
#include <algorithm>

void LevelScreen::Draw() const
{
	m_BlackHole.Draw();
	m_Fence.Draw();
	m_BlackHole2.Draw();
	m_Fence2.Draw();
	
	m_Cannon.Draw();
	
	for (const auto& projectile : m_pVecProjectiles)
	{
		projectile->Draw();
	}
	for (const auto& unit : m_pVecUnits)
	{
		unit->Draw();
	}
	m_Player.Draw();
}

void LevelScreen::Update()
{
	m_Player.Update(*this);
	if (m_Cannon.ReadyToFire())
	{
		m_pVecProjectiles.push_back(m_Cannon.CreateProjectile());
	}

	for (auto& pProjectile : m_pVecProjectiles)
	{
		pProjectile->Update();

		if (not m_LevelBox.IsPointInside(pProjectile->GetPoint()))
			pProjectile->Kill();
	}

	for (auto& unit : m_pVecUnits)
	{
		unit->Update();

		//if (ENGINE.IsKeyPressed('9'))
		{
			for (auto& projectile : m_pVecProjectiles)
			{
				unit->ActOnProjectile(projectile);
			}
		}
	}
	for (auto& projectile : m_pVecProjectiles)
	{
		m_BlackHole.ActOnProjectile(projectile);
		m_Fence.ActOnProjectile(projectile);
		m_BlackHole2.ActOnProjectile(projectile);
		m_Fence2.ActOnProjectile(projectile);
	}

	m_pVecProjectiles.erase(
		std::remove_if(
			m_pVecProjectiles.begin(),
			m_pVecProjectiles.end(),
			[&](const std::unique_ptr<Projectile>& pProjectile)
			{
				return pProjectile->IsDead();
			}),
		m_pVecProjectiles.end()
	);
	
}

void LevelScreen::AddUnit(std::unique_ptr<Unit>&& pUnit)
{
	m_pVecUnits.push_back(std::move(pUnit));
}

void LevelScreen::InputKeyDownThisFrame(int virtualKeyCode)
{
	m_Player.InputKeyDownThisFrame(virtualKeyCode, *this);
}
void LevelScreen::InputKeyUp(int virtualKeyCode)
{
	m_Player.InputKeyUp(virtualKeyCode);
}

const Box& LevelScreen::GetLevelBox() const
{
	return m_LevelBox;
}
