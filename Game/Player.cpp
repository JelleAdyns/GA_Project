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

void Player::Update(LevelScreen& level)
{
	HandleMovementInput(level);
	HandleBorderCollision(level.GetLevelBox());	
}

void Player::InputKeyDownThisFrame(int virtualKeyCode, LevelScreen& level, HUD& hud)
{
	
	switch (virtualKeyCode)
	{
	case _T('R'):
	{
		m_pControlledUnit = nullptr;
		break;
	}
	case VK_SPACE:
	{
		if ( m_pControlledUnit)
		{
			if(not level.IsPointInTile(m_Position))
			{
				if(hud.IsUnitAvailable())
				{
					level.AddUnit(std::move(m_pControlledUnit));
					m_pControlledUnit = nullptr;
					hud.DecreaseAmountAvailable();

					if (not LevelScreen::PICKUP_HINT.second)
					{
						level.SetHint(LevelScreen::PICKUP_HINT.first);
						LevelScreen::PICKUP_HINT.second = true;
					}
				}
			}
			
		}

		if (not m_pControlledUnit)
		{
		 	SetControlledUnit( hud.GetInstaceOfSelectedUnit(Point2f{ m_Position[0],m_Position[1] }));
		}

		break;
	}
	case _T('Q'):
	{
		if (hud.GetAmountOfUnits() > 1)
		{
			hud.SelectPreviousUnit();
			SetControlledUnit(hud.GetInstaceOfSelectedUnit(Point2f{ m_Position[0],m_Position[1] }));
		}
		break;
	}
	case _T('E'):
	{
		if (hud.GetAmountOfUnits() > 1)
		{
			hud.SelectNextUnit();
			SetControlledUnit(hud.GetInstaceOfSelectedUnit(Point2f{ m_Position[0],m_Position[1] }));
		}
		break;
	}
	case _T('X'):
	{
		if(level.PickUpUnit())
		{
			if (not m_Position.RoundedEqual(m_pControlledUnit->GetPos(),0.001f))
			{
				TwoBlade trLine = OneBlade{ -1,0,0,0 } ^ ((m_pControlledUnit->GetPos() & m_Position) | m_Position);
				Motor tr = Motor::Translation(GAUtils::GetDistance(m_pControlledUnit->GetPos(), m_Position), trLine);
				m_pControlledUnit->TranslateUnit(tr);
			}
			while (not hud.IsSameUnit(m_pControlledUnit->GetTypeId()))
			{
				hud.SelectNextUnit();
			}
			hud.IncreaseAmountAvailable();
		}
		break;
	}
	case VK_SHIFT:
	{
		m_Speed = m_DefaultSpeed *2;

		if (not LevelScreen::MODIFY_HINT.second)
		{
			level.SetHint(LevelScreen::MODIFY_HINT.first);
			LevelScreen::MODIFY_HINT.second = true;
		}
		break;
	}
	case VK_LEFT:
	{
		if(m_pControlledUnit) m_pControlledUnit->Action1();
		if (not LevelScreen::PLACE_HINT.second)
		{
			level.SetHint(LevelScreen::PLACE_HINT.first);
			LevelScreen::PLACE_HINT.second = true;
		}
		break;
	}
	case VK_RIGHT:
	{
		if (m_pControlledUnit) m_pControlledUnit->Action2();
		if (not LevelScreen::PLACE_HINT.second)
		{
			level.SetHint(LevelScreen::PLACE_HINT.first);
			LevelScreen::PLACE_HINT.second = true;
		}
		break;
	}
	case VK_UP:
	{
		if (m_pControlledUnit) m_pControlledUnit->Action3();
		if (not LevelScreen::PLACE_HINT.second)
		{
			level.SetHint(LevelScreen::PLACE_HINT.first);
			LevelScreen::PLACE_HINT.second = true;
		}
		break;
	}
	case VK_DOWN:
	{
		if (m_pControlledUnit) m_pControlledUnit->Action4();
		if (not LevelScreen::PLACE_HINT.second)
		{
			level.SetHint(LevelScreen::PLACE_HINT.first);
			LevelScreen::PLACE_HINT.second = true;
		}
		break;
	}
	}
}

void Player::InputKeyUp(int virtualKeyCode)
{
	switch (virtualKeyCode)
	{

	case VK_SHIFT:
	{
		m_Speed = m_DefaultSpeed;
		break;
	}
	
	}
}
void Player::SetControlledUnit(std::unique_ptr<Unit>&& pointerToMove)
{
	if(pointerToMove)
		m_pControlledUnit = std::move(pointerToMove);
}
void Player::HandleMovementInput(LevelScreen& level)
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

		if (not BOOST_HINT.second)
		{
			level.SetHint(BOOST_HINT.first);
			BOOST_HINT.second = true;
			MOVE_HINT.second = true;
		}
	}

	
}
void Player::HandleBorderCollision(const Box& levelBox)
{

	const auto dist = levelBox.GetDistance(m_Position, 20);

	if(dist.Left < 0.f)
	{
		Motor trans = Motor::Translation(dist.Left, OneBlade{ -1,0,0,0 } ^ levelBox.LeftSide);
		GAUtils::Transform(m_Position, trans);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(trans);
	}
	if (dist.Right < 0.f)
	{
		Motor trans = Motor::Translation(dist.Right, OneBlade{ -1,0,0,0 } ^ levelBox.RightSide);
		GAUtils::Transform(m_Position, trans);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(trans);
	}
	if (dist.Bottom < 0.f)
	{
		Motor trans = Motor::Translation(dist.Bottom, OneBlade{ -1,0,0,0 } ^ levelBox.BottomSide);
		GAUtils::Transform(m_Position, trans);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(trans);
	}
	if (dist.Top < 0.f)
	{
		Motor trans = Motor::Translation(dist.Top, OneBlade{ -1,0,0,0 } ^ levelBox.TopSide);
		GAUtils::Transform(m_Position, trans);
		if (m_pControlledUnit) m_pControlledUnit->TranslateUnit(trans);
	}

}


