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
		_pInstance->init(0);
    }
	return _pInstance;
}

void VoiceManager::init(int level) {

	// parsing voices
	tinyxml2::XMLDocument* pVoicesFile = new tinyxml2::XMLDocument();
	synthsystem::IOManager* ioManager = synthsystem::IOManager::getInstance();
	ostringstream ss;
	ss << "levels/0" << level-1 << "/voices.xml";
	pVoicesFile = ioManager->loadXML(ss.str());
	if (pVoicesFile != nullptr) {
		tinyxml2::XMLHandle hDoc(pVoicesFile);
		tinyxml2::XMLElement *pVoicesData;

		pVoicesData = pVoicesFile->FirstChildElement("voice");
		while (pVoicesData) {
			std::string filePath = pVoicesData->Attribute("name");
			_voices.push(filePath);
			pVoicesData = pVoicesData->NextSiblingElement("voice");
		}
	}
}

bool VoiceManager::playNextVoice() {
	if (_voices.size()>0){
		int iPlayingVoice = FmodAudioPlayer::sharedPlayer()->playEffect(("sound/voices/" + _voices.front()).c_str(), 0, 1, 0, 1);
		_voices.pop();
		CCLOG ("Play VOICE now !");
		return true;
	}
	return false;
}

}  // namespace sounds
