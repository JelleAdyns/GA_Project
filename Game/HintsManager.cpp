#include "HintsManager.h"

void HintsManager::Draw() const
{
	//ENGINE.Draw
}

void HintsManager::AddHintToQueue(const tstring& text, float time)
{
	m_HintsQueue.emplace(text, time);
}
