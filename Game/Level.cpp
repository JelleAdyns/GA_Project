#include "Level.h"

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
	m_Player.Update();
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

void Level::InputKeyDown(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{
	case '0':
		m_pVecUnits.push_back(RotatorUnit::CreateUnit());
		break;
	}
	m_Player.InputKeyDown(virtualKeyCode);

}
void Level::InputKeyUp(int virtualKeyCode)
{
	m_Player.InputKeyUp(virtualKeyCode);
}
