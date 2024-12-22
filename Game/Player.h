#ifndef PLAYER_H
#define PLAYER_H

#include "FlyFish.h"
#include "structsf.h"
#include "RotatorUnit.h"
#include <Engine.h>

class Level;
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
	void Update();

	void InputKeyDownThisFrame(int virtualKeyCode, Level& level);
	void InputKeyUp(int virtualKeyCode);
private:

	constexpr static float m_Speed{ 600 };

	TwoBlade m_Direction{ 1,0,0,0,0,0 };
	Motor m_Translation{};

	ThreeBlade m_Position{0,0,0};

	RotatorUnit* m_pControlledRotatorUnit{nullptr};
};

#endif // !PLAYER_H
