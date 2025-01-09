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

		if (not m_LevelBox.IsPointInside(pProjectile->GetPoint(), Projectile::GetRadius()))
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


void LevelScreen::LoadStage()
{

	tifstream inputFile{ jela::ResourceManager::GetInstance().GetDataPath() + _T("StagePattern.txt") };

	tstring info{};

	tstringstream stageTest{};
	while (getline(inputFile, info, _T('/')))
	{
		if (info.find(_T("Stage " + to_tstring(m_StageNumber))) != tstring::npos)
{
			info.erase(0, info.find(to_tstring(m_StageNumber) + _T('\n')));
			stageTest << info;
}
	}
	while (getline(stageTest, info))
	{
		tstring rowString{};
		tstringstream infoStream{ info };
		getline(infoStream, rowString, _T('\"'));
		int row{ std::stoi(rowString) };
		int col{};

		getline(infoStream, rowString);

		const tstring possibleSymbols{ _T(".") };

		while (rowString.find_first_of(possibleSymbols, col) != tstring::npos)
		{
			col = int(rowString.find_first_of(possibleSymbols, col));

			Point2f center
			{
				Tile::GetSize() / 2 + Tile::GetSize() * col,
				Tile::GetSize() / 2 + Tile::GetSize() * row
			};

			bool isIntersection{};

			switch (rowString[col])
{
			case _T('.'):

				m_pVecTiles.emplace_back(std::make_unique<Tile>( center ));
				break;
			}
			++col;
}
}

}
