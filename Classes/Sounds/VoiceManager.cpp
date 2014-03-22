/*!
 * \file VoiceManager.cpp
 * \brief Manages all the sounds of the game from XML files
 * \author Chupee
 * \date 26/02/2014
 */
#include "VoiceManager.h"
#include "FmodAudioPlayer.h"
#include <sstream>

#include "system/IOManager.h"
#include "game/LightMap.h"

namespace sounds {

VoiceManager* VoiceManager::_pInstance = nullptr;

VoiceManager::VoiceManager() {
}

VoiceManager::~VoiceManager() {
}

VoiceManager* VoiceManager::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new VoiceManager();
		//_pInstance->init();
    }
	return _pInstance;
}

void VoiceManager::init(std::string levelName) {
	 CCLOG ("INIT voice mamanger");
	// parsing voices
	synthsystem::IOManager* ioManager = synthsystem::IOManager::getInstance();

	tinyxml2::XMLDocument* pVoicesFile = ioManager->loadXML("levels/" + levelName + "/voices.xml");
	if (pVoicesFile != nullptr) {
		tinyxml2::XMLHandle hDoc(pVoicesFile);
		tinyxml2::XMLElement *pVoicesData;

		pVoicesData = pVoicesFile->FirstChildElement("voice");
		while (pVoicesData) {
			CCLOG ("LOADING one voice");
			std::string filePath = pVoicesData->Attribute("name");
			_voices.push(filePath);
			pVoicesData = pVoicesData->NextSiblingElement("voice");
		}
	}
}

bool VoiceManager::playNextVoice() {
	CCLOG ("I want to play a voice");
	if (_voices.size()>0){
		int iPlayingVoice = FmodAudioPlayer::sharedPlayer()->playEffect(("sound/voices/" + _voices.front()).c_str(), 0, 1, 0, 1);
		_voices.pop();
		CCLOG ("Voice playing");
		return true;
	}
	return false;
}

}  // namespace sounds
