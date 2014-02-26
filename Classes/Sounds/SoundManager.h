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
#include "core/SynthConfig.h"

namespace sounds {

/*! \class SoundManager
 * \brief Manages all the sounds of the game from XML files
 *
 * 
 */
class SoundManager {

public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~SoundManager();

	/*! \brief Get the singleton instance _pInstance */
	static SoundManager* getInstance();

	void init(core::xml data);

	bool playSound(std::string soundName, int iTrackId);

	bool stopSound(int iTrackId);

	bool unmuteMusic(std::string musicName);

	bool muteMusic(std::string musicName);

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

	/*
	 * Classes
	 */

	class Music {
	public:
		int iTrackId;
		std::string filePath;
	};

	class Sound {
	public:
		std::string filePath;
		bool bLoop;
		std::string chainedSoundName;
	};

	/*
	 * Members
	 */

	/*! \brief The singleton instance */
	static SoundManager* _pInstance;

	std::map<std::string,Sound> _sounds;

	std::map<std::string,Music> _musics;

	/**
	 * associate id of playing tracks and the sound which are played on.
	 */
	std::map<int,Sound> _playingSounds;


};

}  // namespace sounds
#endif
