#ifndef COMMANDS_H
#define COMMANDS_H

#include "Game.h"

class Command
{
public:

	Command() = default;

	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;


	virtual void Execute() = 0;
};

class LoadScreenCommand final : public Command
{
public:
	LoadScreenCommand(Game& game, Game::State newGameState) :
		Command{},
		m_NewGameState{ newGameState },
		m_Game{ game }
	{}

	LoadScreenCommand(const LoadScreenCommand& other) = delete;
	LoadScreenCommand(LoadScreenCommand&& other) noexcept = delete;
	LoadScreenCommand& operator=(const LoadScreenCommand& other) = delete;
	LoadScreenCommand& operator=(LoadScreenCommand&& other) noexcept = delete;


	virtual void Execute() override
	{
		m_Game.SetScreen(m_NewGameState);
		m_Game.AddOperationToQueue(Game::ScreenOperation::Set); 
	}

private:
	const Game::State m_NewGameState;
	Game& m_Game;
};

class PushScreenCommand final : public Command
{
public:
	PushScreenCommand(Game& game, Game::State newGameState) :
		Command{},
		m_NewGameState{ newGameState },
		m_Game{ game }
	{}

	PushScreenCommand(const PushScreenCommand& other) = delete;
	PushScreenCommand(PushScreenCommand&& other) noexcept = delete;
	PushScreenCommand& operator=(const PushScreenCommand& other) = delete;
	PushScreenCommand& operator=(PushScreenCommand&& other) noexcept = delete;


	virtual void Execute() override
	{
		m_Game.SetScreen(m_NewGameState);
		m_Game.AddOperationToQueue(Game::ScreenOperation::Push);
	}

private:
	const Game::State m_NewGameState;
	Game& m_Game;
};

class PopScreenCommand final : public Command
{
public:
	PopScreenCommand(Game& game) :
		Command{},
		m_Game{ game }
	{}

	PopScreenCommand(const PopScreenCommand& other) = delete;
	PopScreenCommand(PopScreenCommand&& other) noexcept = delete;
	PopScreenCommand& operator=(const PopScreenCommand& other) = delete;
	PopScreenCommand& operator=(PopScreenCommand&& other) noexcept = delete;


	virtual void Execute() override
	{
		m_Game.AddOperationToQueue(Game::ScreenOperation::Pop);
	}

private:
	Game& m_Game;
};
#endif // !COMMANDS_H

