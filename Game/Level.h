#ifndef LEVEL_H
#define LEVEL_H

#include <memory.h>
#include "Cannon.h"
#include "Unit.h"
#include "RotatorUnit.h"
#include "Player.h"

class Level final
{
public:
	void Draw() const;
	void Update();

	void InputKeyDown(int virtualKeyCode);
	void InputKeyUp(int virtualKeyCode);
private:
	
	Player m_Player{ 0.f,0.f };
	Cannon m_Cannon{};
	std::vector<std::unique_ptr<Projectile>> m_pVecProjectiles{};
	std::vector<std::unique_ptr<Unit>> m_pVecUnits{};
};

#endif // !LEVEL_H
