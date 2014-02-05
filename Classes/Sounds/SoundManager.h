#ifndef SOUNDS_SOUND_MANAGER_H
#define SOUNDS_SOUND_MANAGER_H

#include <map>
#include "System/xml.h"
#include "Sounds/Sound.h"
#include "Sounds/Music.h"

namespace sounds
{
class SoundManager
{
private:
	std::map<string,Sound> _sounds;

	std::map<string,Music> _musics;

	/**
	 * associate id of playing tracks and the sound which are played on.
	 */
	std::map<int,Sound> _playingSounds;


private:
	SoundManager();

public:
	/**
	 *
	 */
	~SoundManager();

	static SoundManager* getInstance();

	void init(system::xml data);

	bool playSound(string soundName, int iTrackId);

	bool stopSound(int iTrackId);

	bool unmuteMusic(string musicName);

	bool muteMusic(string musicName);

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

};

}  // namespace sounds
#endif
