#include "Player.h"
#include "DrawFloatToInt.h"
#include "TeleportUnit.h"
#include "RotatorUnit.h"
#include "Level.h"
#include "GAUtils.h"


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
	if (m_pControlledUnit) m_pControlledUnit->Draw();
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
	case VK_ESCAPE:
	{
		m_pControlledUnit = nullptr;
		break;
	}
	case VK_SPACE:
	{
		if (not m_pControlledUnit)
		{
			auto pUnit = RotatorUnit::CreateUnit(Point2f{ m_Position[0],m_Position[1] });
			m_pControlledUnit.swap( pUnit);
		}
		else
		{
			level.AddUnit(std::move(m_pControlledUnit));
			m_pControlledUnit = nullptr;
		}
		else m_pControlledUnit = nullptr;
		
		break;
	}
	case 'T':
	{
		if (not m_pControlledUnit)
		{
			auto pUnit = TeleportUnit::CreateUnit(Point2f{ m_Position[0],m_Position[1] });
			m_pControlledUnit.swap(pUnit);
		}
		else
		{
			level.AddUnit(std::move(m_pControlledUnit));
			m_pControlledUnit = nullptr;
		}

		break;
	}
	case 'B':
	{
		if (not m_pControlledUnit)
		{
			auto pUnit = BoosterUnit::CreateUnit(Point2f{ m_Position[0],m_Position[1] });
			m_pControlledUnit.swap(pUnit);
		}
		else
		{
			level.AddUnit(std::move(m_pControlledUnit));
			m_pControlledUnit = nullptr;
		}
		else m_pControlledUnit = nullptr;

		break;
	}
	case VK_LEFT:
	{
		if(m_pControlledUnit) m_pControlledUnit->Action1();
		break;
	}
	case VK_RIGHT:
	{
		if (m_pControlledUnit) m_pControlledUnit->Action2();
		break;
	}
	case VK_UP:
	{
		if (m_pControlledUnit) m_pControlledUnit->Action3();
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
		GAUtils::Transform(m_Position, m_Translation);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(m_Translation);
	}

	
}
void Player::HandleBorderCollision(const Box& levelBox)
{

	const jela::Vector2f dist = levelBox.GetOutsideDistance(m_Position);

	if (dist.x != 0.f)
	{
		Motor trans = Motor::Translation(dist.x, TwoBlade{ 1,0,0,0,0,0 });
		GAUtils::Transform(m_Position, trans);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(trans);
	}
	if (dist.y != 0.f)
	{
		Motor trans = Motor::Translation(dist.y, TwoBlade{ 0,1,0,0,0,0 });
		GAUtils::Transform(m_Position, trans);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(trans);
	}

}


