#ifndef HUD_H
#define HUD_H

#include <Engine.h>
#include <typeindex>
#include <vector>
#include "structsf.h"
#include "Tile.h"
#include "Unit.h"
#include "Box.h"

class HUD final
{
public:
	HUD();
	void Draw() const;
	
	void SelectNextUnit();
	void SelectPreviousUnit();
	void Reset();
	void DecreaseAmountAvailable();
	void IncreaseAmountAvailable();
	void AddUnit(std::unique_ptr<Unit>&& pUnit, int amount);

	bool IsSameUnit(std::type_index typeId) const;
	bool IsUnitAvailable() const;

	std::unique_ptr<Unit> GetInstaceOfSelectedUnit(const Point2f& pos) const ;
	Rectf GetArea() const { return m_Area; };
	size_t GetAmountOfUnits() const { return m_VecUnits.size(); };

	constexpr static float GetAreaHeight() { return m_AreaHeight; };


private:

	struct AvailableUnit
	{
		AvailableUnit(std::unique_ptr<Unit>&& unit, int amount) :
			pUnit{std::move(unit)},
			MaxAmount{amount},
			CurrentAmountLeft{amount}
		{}

		std::unique_ptr<Unit> pUnit{ nullptr };
		int MaxAmount{0};
		int CurrentAmountLeft{0};
	};

	constexpr static float m_AreaHeight{ Tile::GetSize()*4.5f};
	const Rectf m_Area
	{
		Tile::GetSize()/4,
		ENGINE.GetWindowRect().height - m_AreaHeight - Tile::GetSize()/4,
		ENGINE.GetWindowRect().width - Tile::GetSize()/2,
		m_AreaHeight
	};

	int m_SelectedIndex{ 0 };
	std::vector<AvailableUnit> m_VecUnits;

	jela::Font& m_rFont{ jela::ResourceManager::GetInstance().GetFont(_T("Arial")) };
};

#endif // !HUD_H