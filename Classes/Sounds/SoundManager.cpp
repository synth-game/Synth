/*!
 * \file SoundManager.cpp
 * \brief Manages all the sounds of the game from XML files
 * \author Chupee
 * \date 26/02/2014
 */
#include "SoundManager.h"
#include "FmodAudioPlayer.h"

#include "system/IOManager.h"
#include "game/LightMap.h"

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
			//effect.eTag = __getSoundType(pEffectData->Attribute("tag"));
			effect.filePath = pEffectData->Attribute("name");
			effect.bLoop = pEffectData->Attribute("isLoop");

			_effects.insert(std::pair<SoundType, Effect>(__getSoundType(pEffectData->Attribute("tag")), effect));
			pEffectData = pEffectData->NextSiblingElement("effect");
		}
	}
}

SoundManager::Effect SoundManager::effectFactory(SoundType type){
	Effect effect = {
		"",
		0
	};
	switch(type) {
		case HERO_START_JUMP:
			effect.filePath = "sound/effects/jump.wav";
			effect.bLoop = 0;
			break;

		default :
			break;
	}

	return effect;
}

bool SoundManager::playMusic(Music music) {
	FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
	_playingMusics.push_back(music.eTag);
	return true;
}

bool SoundManager::playEffect(SoundComponent* component, SoundType type) {

	if (_effects.count(type) == 0){
		_effects.insert(std::make_pair(type, effectFactory(type)));
	}
	Effect effect = _effects[type];
	int index = FmodAudioPlayer::sharedPlayer()->playEffect(effect.filePath.c_str(), effect.bLoop, 1, 0, 1);
	
	if (_playingEffects.count(component) == 0){
		_playingEffects.insert(std::make_pair(component, index));
	}

	return true;
}

bool SoundManager::stopMusic(Music music) {
	FmodAudioPlayer::sharedPlayer()->StopMusicTrack(music.iChannel);
	_playingMusics.erase(std::remove(_playingMusics.begin(), _playingMusics.end(), music.eTag), _playingMusics.end()); 
	return true;
}

bool SoundManager::stopEffect(Effect effect) {
	/*int index = _playingEffects.find(effect)->second;
	FmodAudioPlayer::sharedPlayer()->stopEffect(index);
	_playingEffects.erase(std::remove(_playingEffects.begin(), _playingEffects.end(), _playingEffects.find(effect)), _playingEffects.end()); */
	return true;
}

void SoundManager::updateMusics(Color4B color) {
	Music music = Music();
	if(color != Color4B(0,0,0,0)) {
		if (color == Color4B::BLUE && !isPlayingMusic(SoundType::BLUE) ) {
			music = getMusicFromTag(SoundType::BLUE);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::BLUE);
		} else if (color == Color4B::RED && !isPlayingMusic(SoundType::RED)) {
			music = getMusicFromTag(SoundType::RED);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::RED);
		} else if (color == Color4B::GREEN && !isPlayingMusic(SoundType::GREEN)) {
			music = getMusicFromTag(SoundType::GREEN);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::GREEN);
		} else if (color == Color4B::CYAN && !isPlayingMusic(SoundType::CYAN)) {
			music = getMusicFromTag(SoundType::CYAN);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::CYAN);
		} else if (color == Color4B::MAGENTA && !isPlayingMusic(SoundType::MAGENTA)) {
			music = getMusicFromTag(SoundType::MAGENTA);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::MAGENTA);
		} else if (color == Color4B::YELLOW && !isPlayingMusic(SoundType::YELLOW)) {
			music = getMusicFromTag(SoundType::YELLOW);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::YELLOW);
		} else if (color == Color4B::WHITE && !isPlayingMusic(SoundType::WHITE)) {
			music = getMusicFromTag(SoundType::WHITE);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(music.iChannel);
			_playingMusics.push_back(SoundType::WHITE);
		}
	}
}

bool SoundManager::unmuteMusics() {
	return 0;
}

bool SoundManager::muteMusics() {
	return 0;
}

bool SoundManager::isPlayingMusic(SoundType type) {
	for (auto playingType : _playingMusics) {
		if (playingType == type) {
			return true;
		}
	}
	return false;
}

/*bool SoundManager::Effect::operator<(const Effect & other) const {
	return eTag < other.eTag;
}

bool SoundManager::Effect::operator==(const Effect & other) const {
	return eTag == other.eTag;
}*/


SoundType SoundManager::__getSoundType(std::string sTag) {
	return _tagsMap.find(sTag)->second;
}

}  // namespace sounds
