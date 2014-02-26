/*!
 * \file SoundManager.cpp
 * \brief Manages all the sounds of the game from XML files
 * \author Chupee
 * \date 26/02/2014
 */
#include "SoundManager.h"

namespace sounds {

SoundManager::SoundManager() {
}

SoundManager::~SoundManager() {
}

SoundManager* SoundManager::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new SoundManager();
		_pInstance->init();
    }
	return _pInstance;
}

void SoundManager::init(core::xml data) {
}

bool SoundManager::playSound(std::string soundName, int iTrackId) {
	return 0;
}

bool SoundManager::stopSound(int iTrackId) {
	return 0;
}

bool SoundManager::unmuteMusic(std::string musicName) {
	return 0;
}

bool SoundManager::muteMusic(std::string musicName) {
	return 0;
}

bool SoundManager::isFinished(int iTrackId) {
	return 0;
}

void SoundManager::refresh() {
}

}  // namespace sounds
