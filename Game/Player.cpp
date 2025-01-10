#include "Player.h"
#include "DrawFloatToInt.h"
#include "TeleportUnit.h"
#include "RotatorUnit.h"
#include "BoosterUnit.h"
#include "PhaserUnit.h"
#include "LevelScreen.h"
#include "HUD.h"
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
	ENGINE.SetColor(RGB(255, 255, 0));
	Drawf::DrawEllipse(m_Position[0], m_Position[1],20, 20, 5);
	if (m_pControlledUnit) m_pControlledUnit->Draw();
}

void Player::Update(const LevelScreen& level)
{
	HandleMovementInput();
	HandleBorderCollision(level.GetLevelBox());	
}

void Player::InputKeyDownThisFrame(int virtualKeyCode, LevelScreen& level, HUD& hud)
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
		 	SetControlledUnit( hud.GetInstaceOfSelectedUnit(Point2f{ m_Position[0],m_Position[1] }));
		}
		else
		{
			level.AddUnit(std::move(m_pControlledUnit));
			m_pControlledUnit = nullptr;
		}
		break;
	}
	case _T('Q'):
	{
		hud.SelectPreviousUnit();
		SetControlledUnit(hud.GetInstaceOfSelectedUnit(Point2f{ m_Position[0],m_Position[1] }));
		break;
	}
	case _T('E'):
	{
		hud.SelectNextUnit();
		SetControlledUnit(hud.GetInstaceOfSelectedUnit(Point2f{ m_Position[0],m_Position[1] }));
		break;
	}
	case VK_SHIFT:
	{
		if(level.PickUpUnit())
		{
			if (not m_Position.RoundedEqual(m_pControlledUnit->GetPos(),0.001f))
			{
				TwoBlade trLine = OneBlade{ -1,0,0,0 } ^ ((m_pControlledUnit->GetPos() & m_Position) | m_Position);
				Motor tr = Motor::Translation(GAUtils::GetDistance(m_pControlledUnit->GetPos(), m_Position), trLine);
				m_pControlledUnit->TranslateUnit(tr);
			}
		}
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
	case VK_DOWN:
	{
		if (m_pControlledUnit) m_pControlledUnit->Action4();
		break;
	}
	}
}

void Player::InputKeyUp(int virtualKeyCode)
{
}
void Player::SetControlledUnit(std::unique_ptr<Unit>&& pointerToMove)
{
	if(pointerToMove)
		m_pControlledUnit = std::move(pointerToMove);
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

	const jela::Vector2f dist = levelBox.GetOutsideDistance(m_Position, 20);

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


