#include "Level.h"
#include <algorithm>

void Level::Draw() const
{
	m_Player.Draw();
	m_Cannon.Draw();

	for (const auto& projectile : m_pVecProjectiles)
	{
		projectile->Draw();
	}
	for (const auto& unit : m_pVecUnits)
	{
		unit->Draw();
	}
}

void Level::Update()
{
	m_Player.Update(*this);
	if (m_Cannon.ReadyToFire())
	{
		m_pVecProjectiles.push_back(m_Cannon.CreateProjectile());
	}

	for (auto& projectile : m_pVecProjectiles)
	{
		projectile->Update();
	}
	for (auto& unit : m_pVecUnits)
	{
		unit->Update();
		for (auto& projectile : m_pVecProjectiles)
		{
			unit->ActOnProjectile(projectile);
		}
	}
	}

	m_pVecProjectiles.erase(
		std::remove_if(
			m_pVecProjectiles.begin(),
			m_pVecProjectiles.end(),
			[&](const std::unique_ptr<Projectile>& pProjectile)
			{
				return not m_LevelBox.IsPointInside(pProjectile->GetPoint());
			}),
		m_pVecProjectiles.end()
	);

}

void Level::AddUnit(std::unique_ptr<Unit>&& pUnit)
{
	m_pVecUnits.push_back(std::move(pUnit));
}

void Level::InputKeyDownThisFrame(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case '0':
		//m_pVecUnits.push_back(RotatorUnit::CreateUnit());
		break;
	}
	m_Player.InputKeyDownThisFrame(virtualKeyCode, *this);

}
void Level::InputKeyUp(int virtualKeyCode)
{
	m_Player.InputKeyUp(virtualKeyCode);
}

const Box& Level::GetLevelBox() const
{
	return m_LevelBox;
}
