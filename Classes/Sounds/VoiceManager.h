/*!
 * \file VoiceManager.h
 * \brief Manages all the sounds of the game from XML files
 * \author Tom
 * \date 18/03/2014
 */
#ifndef SOUNDS_VOICE_MANAGER_H
#define SOUNDS_VOICE_MANAGER_H

#include <queue>
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
class VoiceManager {

public:

	/*
	 * Classes
	 */

	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~VoiceManager();

	/*! \brief Get the singleton instance _pInstance */
	static VoiceManager* getInstance();

	void init(int level);

	bool playNextVoice();

private:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	VoiceManager();

	/*
	 * Members
	 */

	/*! \brief The singleton instance */
	static VoiceManager* _pInstance;

	std::queue<std::string> _voices;

};

}  // namespace sounds
#endif
