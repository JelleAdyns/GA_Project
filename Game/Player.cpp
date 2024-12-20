#include "Player.h"
#include "DrawFloatToInt.h"


Player::Player(float x, float y) :
	m_Position{ x, y, 0}
{

}
Player::Player(const Point2f& pos):
	Player{pos.x,pos.y}
{
}

void Player::Draw() const
{
	Drawf::DrawEllipse(m_Position[0], m_Position[1],50, 50);
}

void Player::Update()
{
	auto dt = ENGINE.GetDeltaTime();
	m_Direction = {};
	if (ENGINE.IsKeyPressed('W')) m_Direction += TwoBlade{ 0,1,0,0,0,0 };
	if (ENGINE.IsKeyPressed('A')) m_Direction += TwoBlade{ -1,0,0,0,0,0 };
	if (ENGINE.IsKeyPressed('S')) m_Direction += TwoBlade{ 0,-1,0,0,0,0 };
	if (ENGINE.IsKeyPressed('D')) m_Direction += TwoBlade{ 1,0,0,0,0,0 };
	if (!m_Direction.RoundedEqual({}, 0.001f))
	{
		m_Translation = Motor::Translation(m_Speed * dt, m_Direction);
		m_Position = (m_Translation * m_Position * ~m_Translation).Grade3();
	}
}

void Player::InputKeyDown(int virtualKeyCode)
{

}

void Player::InputKeyUp(int virtualKeyCode)
{
}
