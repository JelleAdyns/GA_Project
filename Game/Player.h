#ifndef PLAYER_H
#define PLAYER_H

#include <Engine.h>
#include "Unit.h"
#include "Box.h"
#include "HintBox.h"

class LevelScreen;

class HUD;
class Player final
{
public:
	Player(float x, float y);
	Player(const Point2f& pos);

	~Player() = default;

	Player(const Player& other) = delete;
	Player(Player&& other) noexcept = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) noexcept = delete;

	void Draw() const;
	void Update(LevelScreen& level);

	void InputKeyDownThisFrame(int virtualKeyCode, LevelScreen& level, HUD& hud);
	void InputKeyUp(int virtualKeyCode);

	void SetControlledUnit(std::unique_ptr<Unit>&& pointerToMove);
	bool OwnsUnit() const {	return m_pControlledUnit ? true : false;}

	ThreeBlade GetPos() const { return m_Position; }

	static inline std::pair<HintBox, bool> MOVE_HINT{ std::make_pair<HintBox, bool>({_T("Move with WASD."),10, Rectf{ 50,-50,200,100 },true }, false) };
	static inline std::pair<HintBox, bool> BOOST_HINT{ std::make_pair<HintBox, bool>({_T("Boost with SHIFT."),10, Rectf{ 50,-50,200,100 },true }, false) };

private:
	void HandleMovementInput(LevelScreen& level);
	void HandleBorderCollision(const Box& levelBox);
	
	constexpr static float m_DefaultSpeed{ 150 };
	float m_Speed{ m_DefaultSpeed};

	TwoBlade m_Direction{ 1,0,0,0,0,0 };
	Motor m_Translation{};

	ThreeBlade m_Position{0,0,0};
	std::unique_ptr<Unit> m_pControlledUnit{ nullptr };
};

#endif // !PLAYER_H
