#include "SoundManager.h"

namespace sounds
{

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

SoundManager* SoundManager::getInstance()
{
	return 0;
}

void SoundManager::init(system::xml data)
{
}

bool SoundManager::playSound(string soundName, int iTrackId)
{
	return 0;
}

bool SoundManager::stopSound(int iTrackId)
{
	return 0;
}

bool SoundManager::unmuteMusic(string musicName)
{
	return 0;
}

bool SoundManager::muteMusic(string musicName)
{
	return 0;
}

bool SoundManager::isFinished(int iTrackId)
{
	return 0;
}

void SoundManager::refresh()
{
}
}  // namespace sounds
