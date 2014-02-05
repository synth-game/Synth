#ifndef SOUNDS_SOUND_H
#define SOUNDS_SOUND_H

namespace sounds
{
/**
 * Classe interne privée de SoundManager
 */
class Sound
{
public:
	string filePath;

	bool bLoop;

	string chainedSoundName;

};

}  // namespace sounds
#endif
