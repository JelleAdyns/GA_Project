#include "Player.h"
#include "DrawFloatToInt.h"
#include "Level.h"


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

void Player::Update(const Level& level)
{
	HandleMovementInput();
	HandleBorderCollision(level.GetLevelBox());	
	}

void Player::InputKeyDownThisFrame(int virtualKeyCode, Level& level)
{
	switch (virtualKeyCode)
	{
	case VK_SPACE:
	{
		if (not m_pControlledRotatorUnit)
		{
			auto pUnit = RotatorUnit::CreateUnit(Point2f{ m_Position[0],m_Position[1] });
			m_pControlledRotatorUnit = pUnit.get();
			level.AddUnit(std::move(pUnit));
		}
		else m_pControlledRotatorUnit = nullptr;
		
		break;
	}
	case VK_LEFT:
	{
		if(m_pControlledRotatorUnit) m_pControlledRotatorUnit->AddStartAngle();
		break;
	}
	case VK_RIGHT:
	{
		if (m_pControlledRotatorUnit) m_pControlledRotatorUnit->SwitchDegrees();
		break;
	}
	case VK_UP:
	{
		if (m_pControlledRotatorUnit) m_pControlledRotatorUnit->ToggleDirection();
		break;
	}
	}
}

void Player::InputKeyUp(int virtualKeyCode)
{
}
void Player::HandleMovementInput()
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
void Player::HandleBorderCollision(const Box& levelBox)
{

	const Point2f dist = levelBox.GetOutsideDistance(m_Position);

	if (dist.x != 0.f)
	{
		Motor trans = Motor::Translation(dist.x, TwoBlade{ 1,0,0,0,0,0 });
		m_Position = (trans * m_Position * ~trans).Grade3();
	}
	if (dist.y != 0.f)
	{
		Motor trans = Motor::Translation(dist.y, TwoBlade{ 0,1,0,0,0,0 });
		m_Position = (trans * m_Position * ~trans).Grade3();
	}
}


