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
	std::unique_ptr<Unit> GetInstaceOfSelectedUnit(const Point2f& pos) const ;
	constexpr static float GetAreaHeight() { return m_AreaHeight; };

private:
	constexpr static float m_AreaHeight{ Tile::GetSize()*5};
	Rectf m_Area
	{
		0.f,
		ENGINE.GetWindowRect().height - m_AreaHeight,
		static_cast<float>(ENGINE.GetWindowRect().width),
		m_AreaHeight
	};

	int m_IndexSelectedUnit{ 0 };
	std::vector<std::unique_ptr<Unit>> m_VecUnitsToSelect;
};

#endif // !HUD_H