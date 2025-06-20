#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include <memory>
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
#include "HUD.h"
#include "Commands.h"
#include "HintBox.h"
#include "Game.h"

class LevelScreen final : public Screen
{
public:
	LevelScreen(Game& game);
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
	bool PickUpUnit();
	bool IsPointInTile(const ThreeBlade& point) const;
	void SetHint(const HintBox& hint);


	static inline std::pair<HintBox, bool> SELECT_HINT{ std::make_pair<HintBox, bool>({_T("Select unit with Q and E."),20, Rectf{},false }, false) };
	static inline std::pair<HintBox, bool> MODIFY_HINT{ std::make_pair<HintBox, bool>({_T("Modify unit with the ARROWS."),10, Rectf{ 50,-50,200,100 },true }, false) };
	static inline std::pair<HintBox, bool> PLACE_HINT{ std::make_pair<HintBox, bool>({_T("Place unit with SPACE."),10, Rectf{ 50,-50,200,100 },true }, false) };
	static inline std::pair<HintBox, bool> PICKUP_HINT{ std::make_pair<HintBox, bool>({_T("Pick up unit with X when in range."),10, Rectf{ 50,-50,200,100 },true }, false) };

private:
	HintBox m_Hint{};

	std::unique_ptr<Command> m_pPauseCommand{nullptr};
	std::unique_ptr<Command> m_pVictoryCommand{nullptr};

	HUD m_HUD{};
	const Box m_LevelBox;
	Cannon m_Cannon{1.f};
	Player m_Player{ m_LevelBox.Center[0], m_LevelBox.Center[1] };
	std::vector<std::unique_ptr<Target>> m_pVecTargets{};
	std::vector<std::unique_ptr<Projectile>> m_pVecProjectiles{};
	std::vector<std::unique_ptr<Unit>> m_pVecUnits{};
	std::vector<std::unique_ptr<Tile>> m_pVecTiles{};

	int m_StageNumber{0};
	int m_MaxStages{6};

	bool LevelCompleted() const;
	void Reset();
	void CheckForUnitPickUp() const;
	void EraseRemovedUnits();
	void EraseDeadTargets();
	void EraseDeadProjectiles();
	void LoadStage();
};

#endif // !LEVELSCREEN_H
