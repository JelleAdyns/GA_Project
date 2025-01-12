#include <queue>
#include <Engine.h>
#ifndef HINTSMANAGER_H
#define HINTSMANAGER_H

class HintsManager final
{
public:
    static HintsManager& GetInstance()
    {
        static HintsManager hintsMan = HintsManager{};
        return hintsMan;
    }
  
    ~HintsManager() = default;

    HintsManager(const HintsManager&) = delete;
    HintsManager(HintsManager&&) noexcept = delete;
    HintsManager& operator= (const HintsManager&) = delete;
    HintsManager& operator= (HintsManager&&) noexcept = delete;

    void Draw() const;
    void Update();

    void AddHintToQueue(const tstring& text, float time);

private:
    HintsManager() = default;

    std::queue<std::pair<tstring, float>> m_HintsQueue{};
};

#endif // !HINTSMANAGER_H
