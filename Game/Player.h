#ifndef PLAYER_H
#define PLAYER_H

#include <Engine.h>
#include "Unit.h"
#include "Box.h"

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
	void Update(const LevelScreen& level);

	void InputKeyDownThisFrame(int virtualKeyCode, LevelScreen& level, HUD& hud);
	void InputKeyUp(int virtualKeyCode);

	void HandleMovementInput();
	void HandleBorderCollision(const Box& levelBox);
private:

	constexpr static float m_Speed{ 400 };

	TwoBlade m_Direction{ 1,0,0,0,0,0 };
	Motor m_Translation{};

	ThreeBlade m_Position{0,0,0};
	std::unique_ptr<Unit> m_pControlledUnit{ nullptr };
};

#endif // !PLAYER_H
