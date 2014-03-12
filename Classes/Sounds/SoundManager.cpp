/*!
 * \file SoundManager.cpp
 * \brief Manages all the sounds of the game from XML files
 * \author Chupee
 * \date 26/02/2014
 */
#include "SoundManager.h"
#include "FmodAudioPlayer.h"

#include "system/IOManager.h"

#define MUSIC_NUMBER 7

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
	_tagsMap.insert(std::pair<std::string, SoundType>(	"BACKGROUND",			SoundType::BACKGROUND	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"RED",					SoundType::RED	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"BLUE",					SoundType::BLUE	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"GREEN",				SoundType::GREEN	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"YELLOW",				SoundType::YELLOW	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"CYAN",					SoundType::CYAN	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"MAGENTA",				SoundType::MAGENTA	));
	_tagsMap.insert(std::pair<std::string, SoundType>(	"WHITE",				SoundType::WHITE	));
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
	synthsystem::IOManager* ioManager = synthsystem::IOManager::getInstance();
	pMusicsFile = ioManager->loadXML("xml/musics.xml");
	if (pMusicsFile != nullptr) {
		tinyxml2::XMLHandle hDoc(pMusicsFile);
		tinyxml2::XMLElement *pMusicData;
		Music music;
		int i = MUSIC_NUMBER - 1;

		pMusicData = pMusicsFile->FirstChildElement("music");
		while (pMusicData) {	
			music = Music();
			music.eTag = __getSoundType(pMusicData->Attribute("tag"));
			music.filePath = pMusicData->Attribute("name");
			music.iChannel = i;
			_musics.insert(std::pair<SoundType, Music>(music.eTag, music));
			FmodAudioPlayer::sharedPlayer()->InitMusic("sound/music/"+music.filePath);
			--i;
			pMusicData = pMusicData->NextSiblingElement("music");
		}

		for (auto musicData : _musics) {
			Music playMusic = musicData.second;
			//FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(playMusic.iChannel);
		}

	}

	// parsing effects
	tinyxml2::XMLDocument* pEffectsFile = new tinyxml2::XMLDocument();
	pEffectsFile = ioManager->loadXML("xml/effects.xml");
	if (pEffectsFile != nullptr) {
		tinyxml2::XMLHandle hDoc(pEffectsFile);
		tinyxml2::XMLElement *pEffectData;
		Effect effect;
		std::string next;

		pEffectData = pEffectsFile->FirstChildElement("effect");
		while (pEffectData) {	
			effect = Effect();
			effect.eTag = __getSoundType(pEffectData->Attribute("tag"));
			effect.filePath = pEffectData->Attribute("name");
			effect.bLoop = pEffectData->Attribute("isLoop");
			effect.nextTag = SoundType();
			next = pEffectData->Attribute("next");
			if (!next.empty()) {
				effect.nextTag = __getSoundType(next);
			}
			_effects.insert(std::pair<SoundType, Effect>(effect.eTag, effect));
			pEffectData = pEffectData->NextSiblingElement("effect");
		}
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

SoundType SoundManager::__getSoundType(std::string sTag) {
	return _tagsMap.find(sTag)->second;
}

}  // namespace sounds
