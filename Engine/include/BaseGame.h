#ifndef BASEGAME_H
#define BASEGAME_H

namespace jela
{
    class BaseGame
    {
    public:
        BaseGame() = default;
        virtual ~BaseGame() = default;

        BaseGame(const BaseGame& other) = delete;
        BaseGame(BaseGame&& other) noexcept = delete;
        BaseGame& operator=(const BaseGame& other) = delete;
        BaseGame& operator=(BaseGame&& other) noexcept = delete;

        virtual void Initialize() = 0;
        virtual void Cleanup() = 0;

        virtual void Draw() const = 0;
        virtual void Tick() = 0;
        virtual void KeyDown(int virtualKeycode) = 0;
        virtual void KeyDownThisFrame(int virtualKeycode) = 0;
        virtual void KeyUp(int virtualKeycode) = 0;
        virtual void HandleControllerInput() = 0;
        virtual void MouseDown(bool isLeft, int x, int y) = 0;
        virtual void MouseUp(bool isLeft, int x, int y) = 0;
        virtual void MouseMove(int x, int y, int keyDown) = 0;
        virtual void MouseWheelTurn(int x, int y, int turnDistance, int keyDown) = 0;
    };

}
#endif // !BASEGAME_H