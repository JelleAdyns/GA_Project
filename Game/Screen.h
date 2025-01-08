#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "Engine.h"

class Screen
{
public:
	Screen() = default;
	virtual ~Screen() = default;

	Screen(const Screen& other) = delete;
	Screen(Screen&& other) noexcept = delete;
	Screen& operator=(const Screen& other) = delete;
	Screen& operator=(Screen&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update() = 0;
	virtual void InputKeyDownThisFrame(int virtualKeyCode) = 0;
	virtual void InputKeyUp(int virtualKeyCode) = 0;
	virtual void HandleControllerInput() = 0;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void OnSuspend() = 0;
	virtual void OnResume() = 0;

	//struct KeybindString
	//{
	//	const tstring keyboard{};
	//	const tstring controller{};
	//
	//	const tstring& GetActiveString() const
	//	{
	//		return ENGINE.IsKeyBoardActive() ? keyboard : controller;
	//	}
	//};
};

#endif // !SCREEN_H