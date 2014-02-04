#include "SoundManager.h"

namespace Sounds
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

void SoundManager::init(System::xml data)
{
}

boolean SoundManager::playSound(string soundName, int iTrackId)
{
	return 0;
}

boolean SoundManager::stopSound(int iTrackId)
{
	return 0;
}

boolean SoundManager::unmuteMusic(string musicName)
{
	return 0;
}

boolean SoundManager::muteMusic(string musicName)
{
	return 0;
}

boolean SoundManager::isFinished(int iTrackId)
{
	return 0;
}

void SoundManager::refresh()
{
}
}  // namespace Sounds
