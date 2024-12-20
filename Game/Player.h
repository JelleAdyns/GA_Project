#ifndef PLAYER_H
#define PLAYER_H

#include "FlyFish.h"
#include "structsf.h"
#include <Engine.h>

class Player final
{
public:
	Player(float x, float y);
	Player(const Point2f& pos);

	void Draw() const;
	void Update();

	void InputKeyDown(int virtualKeyCode);
	void InputKeyUp(int virtualKeyCode);
private:

	constexpr static float m_Speed{ 1000 };

	TwoBlade m_Direction{ 1,0,0,0,0,0 };
	Motor m_Translation{};

	ThreeBlade m_Position{0,0,0};
};

#endif // !PLAYER_H
