#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include <memory.h>
#include "Cannon.h"
#include "Unit.h"
#include "Box.h"
#include "RotatorUnit.h"
#include "Player.h"
#include "Tile.h"
#include "BlackHoleTile.h"
#include "FenceTile.h"
#include "Screen.h"
#include "Target.h"

class Game;
class LevelScreen final : public Screen
{
public:
	LevelScreen(Game& game) :
		Screen{},
		m_LevelBox{
			ENGINE.GetWindowRect().width / 2.f,
			ENGINE.GetWindowRect().height / 2.f,
			static_cast<float>(ENGINE.GetWindowRect().width),
			static_cast<float>(ENGINE.GetWindowRect().height) }
	{}
		LoadStage();
		m_pVecTargets.emplace_back(std::make_unique<Target>(60.f, 300.f));
	}

	~LevelScreen() = default;

	LevelScreen(const LevelScreen& other) = delete;
	LevelScreen(LevelScreen&& other) noexcept = delete;
	LevelScreen& operator=(const LevelScreen& other) = delete;
	LevelScreen& operator=(LevelScreen&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update() override;

	virtual void InputKeyDownThisFrame(int virtualKeyCode) override;
	virtual void InputKeyUp(int virtualKeyCode) override;
	virtual void HandleControllerInput() override {};

	virtual void OnEnter() override {};
	virtual void OnExit() override {};
	virtual void OnSuspend() override {};
	virtual void OnResume() override {};

	void AddUnit(std::unique_ptr<Unit>&& pUnit);
	const Box& GetLevelBox() const;
private:

	const Box m_LevelBox;
	Player m_Player{ 120.f,160.f };
	Cannon m_Cannon{};
	std::vector<std::unique_ptr<Target>> m_pVecTargets{};
	std::vector<std::unique_ptr<Projectile>> m_pVecProjectiles{};
	std::vector<std::unique_ptr<Unit>> m_pVecUnits{};
	std::vector<std::unique_ptr<Tile>> m_pVecTiles{};

	int m_StageNumber{};

	void EraseDeadTargets();
	void EraseDeadProjectiles();
	void LoadStage();
};

#endif // !LEVELSCREEN_H
