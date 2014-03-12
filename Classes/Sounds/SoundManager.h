/*!
 * \file SoundManager.h
 * \brief Manages all the sounds of the game from XML files
 * \author Chupee
 * \date 26/02/2014
 */
#ifndef SOUNDS_SOUND_MANAGER_H
#define SOUNDS_SOUND_MANAGER_H

#include <map>
#include <string>
#include "cocos2d.h"
#include "core/SynthConfig.h"
#include "SoundType.h"
#include "FmodAudioPlayer.h"
#include "game/LightMap.h"

USING_NS_CC;

namespace sounds {

/*! \class SoundManager
 * \brief Manages all the sounds of the game from XML files
 *
 * 
 */
class SoundManager {

public:

	/*
	 * Classes
	 */

	class Music {
	public:
		SoundType eTag;
		std::string filePath;
		int iChannel;
	};

	class Effect {
	public:
		SoundType eTag;
		std::string filePath;
		bool bLoop;
		SoundType nextTag;
	};

	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~SoundManager();

	/*! \brief Get the singleton instance _pInstance */
	static SoundManager* getInstance();

	void init();

	inline Music getMusicFromTag(SoundType type) { return _musics.find(type)->second; }

	bool playSound(std::string soundName, int iTrackId);

	bool stopSound(int iTrackId);

	void updateMusics(Color4B color);

	bool unmuteMusic(std::string musicName);

	bool muteMusic(std::string musicName);

	bool isPlayingMusic(SoundType type);

	/**
	 * = true :
	 *  if iTrackId isn't in _playingSounds map
	 */
	bool isFinished(int iTrackId);

	/**
	 * This function is useful to manage chained sound.
	 * Browse every playing sound. Check if they are finished. If yes, launch the chained sound
	 */
	void refresh();

private:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	SoundManager();

	SoundType __getSoundType(std::string sTag);

	

	/*
	 * Members
	 */

	/*! \brief The singleton instance */
	static SoundManager* _pInstance;

	std::map<SoundType,Effect> _effects;

	std::map<SoundType,Music> _musics;

	std::vector<SoundType> _playingMusics;

	/*! \brief Associate the string tag to the SoundType tag */
	std::map<std::string,SoundType> _tagsMap;


};

}  // namespace sounds
#endif
