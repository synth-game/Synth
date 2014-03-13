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
#include "sounds/SoundComponent.h"

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

	struct Music {
		SoundType eTag;
		std::string filePath;
		int iChannel;
	};

	struct Effect {
		std::string filePath;
		bool bLoop;

		//bool operator<(const Effect&) const;
		//bool operator==(const Effect&) const;
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

	bool playMusic(Music music);
	bool playEffect(SoundComponent* component, SoundType type);

	bool stopMusic(Music music);
	bool stopEffect(Effect effect);

	void updateMusics(Color4B color);

	bool unmuteMusics();

	bool muteMusics();

	bool isPlayingMusic(SoundType type);

	bool isPlayingEffect(SoundType type);

	


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

	std::map<SoundComponent*, std::tuple<SoundType, int>> _playingEffects;

	/*! \brief Associate the string tag to the SoundType tag */
	std::map<std::string,SoundType> _tagsMap;
	
	Effect effectFactory(SoundType type);

};

}  // namespace sounds
#endif
