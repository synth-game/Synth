/*!
 * \file SoundManager.cpp
 * \brief Manages all the sounds of the game from XML files
 * \author Chupee
 * \date 26/02/2014
 */
#include "SoundManager.h"

namespace sounds {

SoundManager* SoundManager::_pInstance = nullptr;

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

void SoundManager::init() {

	// invert enum animation type
	_tagsMap.insert(std::pair<std::string, SoundType>(	"HERO_WALK",			SoundType::HERO_WALK	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"HERO_HIT",				SoundType::HERO_HIT	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"HERO_BOUNCE",			SoundType::HERO_BOUNCE	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"HERO_COUGH",			SoundType::HERO_COUGH	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"HERO_START_JUMP",		SoundType::HERO_START_JUMP	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"HERO_FLY",				SoundType::HERO_FLY	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"FIREFLY_INTERACT",		SoundType::FIREFLY_INTERACT	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"FIREFLY_MOVE",			SoundType::FIREFLY_MOVE	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"FIREFLY_OFF",			SoundType::FIREFLY_OFF	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"FIREFLY_ON",			SoundType::FIREFLY_ON	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"LIGHTSWITCH",			SoundType::LIGHTSWITCH	));

	// parsing musics
	tinyxml2::XMLDocument* pMusicsFile = new tinyxml2::XMLDocument();
	int xmlmusicserror = pMusicsFile->LoadFile("xml/musics.xml");
	if(xmlmusicserror == 0) {
		CCLOG("NO ERROR WHILE LOADING XML FILE !!!!!!!!! : %d", xmlmusicserror);
		tinyxml2::XMLHandle hDoc(pMusicsFile);
		tinyxml2::XMLElement *pMusicData;
		std::string tag = "";

		pMusicData = pMusicsFile->FirstChildElement("music");
		while(pMusicData)
		{	
			tag = pMusicData->Attribute("tag");
			CCLOG("MUSIC tag: %s PARSED !", tag.c_str());
			pMusicData = pMusicData->NextSiblingElement("music");
		}
	} else {
		CCLOG("ERROR WHILE LOADING XML FILE !!!!!!!!! : %d", xmlmusicserror);
	}

	// parsing effects
	tinyxml2::XMLDocument* pEffectsFile = new tinyxml2::XMLDocument();
	int xmleffectserror = pEffectsFile->LoadFile("xml/effects.xml");
	if(xmleffectserror == 0) {
		CCLOG("NO ERROR WHILE LOADING XML FILE !!!!!!!!! : %d", xmleffectserror);
		tinyxml2::XMLHandle hDoc(pEffectsFile);
		tinyxml2::XMLElement *pEffectData;
		std::string tag = "";

		pEffectData = pEffectsFile->FirstChildElement("effect");
		while(pEffectData)
		{	
			tag = pEffectData->Attribute("tag");
			CCLOG("EFFECT tag: %s PARSED !", tag.c_str());
			pEffectData = pEffectData->NextSiblingElement("effect");
		}
	} else {
		CCLOG("ERROR WHILE LOADING XML FILE !!!!!!!!! : %d", xmleffectserror);
	}
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
