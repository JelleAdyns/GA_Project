#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include <memory.h>
#include "Cannon.h"
#include "Unit.h"
#include "Box.h"
#include "RotatorUnit.h"
#include "Player.h"
#include "BlackHoleTile.h"
#include "FenceTile.h"
#include "Screen.h"

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
	std::vector<std::unique_ptr<Projectile>> m_pVecProjectiles{};
	std::vector<std::unique_ptr<Unit>> m_pVecUnits{};
	BlackHoleTile m_BlackHole{ Point2f{300,200} };
	BlackHoleTile m_BlackHole2{ Point2f{340,200} };
	FenceTile m_Fence{ Point2f{400,200} };
	FenceTile m_Fence2{ Point2f{440,200} };
};

#endif // !LEVELSCREEN_H
