#include "LevelScreen.h"
#include "GAUtils.h"
#include <algorithm>

void LevelScreen::Draw() const
{

	m_Cannon.Draw();
	
	for (const auto& pTile : m_pVecTiles)
	{
		pTile->Draw();
	}
	for (const auto& pUnit : m_pVecUnits)
	{
		pUnit->Draw();
	}
	for (const auto& pProjectile : m_pVecProjectiles)
	{
		pProjectile->Draw();
	}
	for (const auto& pTarget : m_pVecTargets)
	{
		pTarget->Draw();
	}
	m_Player.Draw();
	m_HUD.Draw();
}

void LevelScreen::Update()
{

	m_Player.Update(*this);
	if (m_Cannon.ReadyToFire())
	{
		m_pVecProjectiles.push_back(m_Cannon.CreateProjectile());
	}

	for (const auto& pTarget : m_pVecTargets)
	{
		pTarget->Update();
	}
	for (const auto& pProjectile : m_pVecProjectiles)
	{
		pProjectile->Update();

		if (not m_LevelBox.IsPointInside(pProjectile->GetPoint(), Projectile::GetRadius()))
			pProjectile->Kill();
	}

	CheckForUnitPickUp();
	for (const auto& pUnit : m_pVecUnits)
	{
		pUnit->Update();

		for (auto& projectile : m_pVecProjectiles)
		{
			pUnit->ActOnProjectile(projectile);
		}
		
	}
	for (const auto& pTile : m_pVecTiles)
	{
		for (auto& projectile : m_pVecProjectiles)
		{
			pTile->ActOnProjectile(projectile);
		}
	}
	for (const auto& pProjectile : m_pVecProjectiles)
	{
		for (auto& pTarget : m_pVecTargets)
		{
			if (pTarget and pTarget->GetHitBox().IsPointInside(pProjectile->GetPoint()))
			{
				pTarget->DealDamage();
				pProjectile->Kill();
				if (pTarget->IsDead())
				{
					pTarget = nullptr;
				}
			}
		}
	}
	EraseDeadProjectiles();
	EraseDeadTargets();

	if (LevelCompleted())
	{
		Reset();
		++m_StageNumber %= m_MaxStages;
		LoadStage();
	}

}

void LevelScreen::AddUnit(std::unique_ptr<Unit>&& pUnit)
{
	m_pVecUnits.push_back(std::move(pUnit));
}

void LevelScreen::InputKeyDownThisFrame(int virtualKeyCode)
{
	m_Player.InputKeyDownThisFrame(virtualKeyCode, *this, m_HUD);
}
void LevelScreen::InputKeyUp(int virtualKeyCode)
{
	m_Player.InputKeyUp(virtualKeyCode);
}

const Box& LevelScreen::GetLevelBox() const
{
	return m_LevelBox;
}

bool LevelScreen::PickUpUnit()
{
	bool pickedUp{ false };
	for (auto& pUnit : m_pVecUnits)
	{
		if (pUnit->PickUpAvailable())
		{
			pUnit->ShowPickUpRadius(false);
			m_Player.SetControlledUnit(std::move(pUnit));
			pickedUp = true;
			break;
		}
	}

	if(pickedUp) EraseRemovedUnits();
	return pickedUp;
}

bool LevelScreen::IsPointInTile(const ThreeBlade& point)
{
	for (const auto& pTile : m_pVecTiles)
	{
		if (pTile->IsPointInside(point))
			return true;
	}
	return false;
}

bool LevelScreen::LevelCompleted() const
{
	return m_pVecTargets.empty();
}

void LevelScreen::Reset()
{
	m_pVecProjectiles.clear();
	m_pVecUnits.clear();
	m_pVecTiles.clear();
	m_pVecTargets.clear();
}

void LevelScreen::CheckForUnitPickUp() const
{

	std::vector<Unit*> copyVector{};

	for (auto& pUnit : m_pVecUnits)
	{
		if (GAUtils::GetDistance(pUnit->GetPos(), m_Player.GetPos()) < Unit::GetPickUpRadius())
			copyVector.push_back(pUnit.get());
		else pUnit->ShowPickUpRadius(false);
	}

	std::sort(copyVector.begin(), copyVector.end(),
		[&](const Unit* pUnit1, const Unit* pUnit2)
		{
			return GAUtils::GetDistance(m_Player.GetPos(), pUnit1->GetPos()) < GAUtils::GetDistance(m_Player.GetPos(), pUnit2->GetPos());
		});

	if (not copyVector.empty())
	{
		(*copyVector.cbegin())->ShowPickUpRadius(true);

		std::for_each(std::next(copyVector.cbegin()), copyVector.cend(),
			[](Unit* pUnit) {pUnit->ShowPickUpRadius(false); });
	}
	
}

void LevelScreen::EraseRemovedUnits()
{
	m_pVecUnits.erase(
		std::remove_if(
			m_pVecUnits.begin(),
			m_pVecUnits.end(),
			[](const std::unique_ptr<Unit>& pUnit)
			{
				return pUnit == nullptr;
			}),
		m_pVecUnits.end()
	);
}

void LevelScreen::EraseDeadTargets()
{
	m_pVecTargets.erase(
		std::remove_if(
			m_pVecTargets.begin(),
			m_pVecTargets.end(),
			[](const std::unique_ptr<Target>& pTarget)
			{
				return pTarget == nullptr;
			}),
		m_pVecTargets.end()
	);
}

void LevelScreen::EraseDeadProjectiles()
{
	m_pVecProjectiles.erase(
		std::remove_if(
			m_pVecProjectiles.begin(),
			m_pVecProjectiles.end(),
			[](const std::unique_ptr<Projectile>& pProjectile)
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

		const tstring possibleSymbols{ _T(".BFT") };

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

			case _T('B'):
				m_pVecTiles.emplace_back(std::make_unique<BlackHoleTile>(center));
				break;

			case _T('F'):
				m_pVecTiles.emplace_back(std::make_unique<FenceTile>(center));
				break;

			case _T('T'):
				m_pVecTargets.emplace_back(std::make_unique<Target>(center));
				break;
			}
			++col;
		}
	}

}
