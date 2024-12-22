#ifndef LEVEL_H
#define LEVEL_H

#include <memory.h>
#include "Cannon.h"
#include "Unit.h"
#include "Box.h"
#include "RotatorUnit.h"
#include "Player.h"

class Level final
{
public:
	Level():
	m_LevelBox{
		ENGINE.GetWindowRect().width / 2.f,
		ENGINE.GetWindowRect().height / 2.f,
		static_cast<float>(ENGINE.GetWindowRect().width),
		static_cast<float>(ENGINE.GetWindowRect().height) }
	{}

	~Level() = default;

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Draw() const;
	void Update();

	void AddUnit(std::unique_ptr<Unit>&& pUnit);

	void InputKeyDownThisFrame(int virtualKeyCode);
	void InputKeyUp(int virtualKeyCode);
	const Box& GetLevelBox() const;
private:
	
	const Box m_LevelBox;
	Player m_Player{ 120.f,160.f };
	Cannon m_Cannon{};
	std::vector<std::unique_ptr<Projectile>> m_pVecProjectiles{};
	std::vector<std::unique_ptr<Unit>> m_pVecUnits{};
};

#endif // !LEVEL_H
