#ifndef SOUNDS_SOUND_H
#define SOUNDS_SOUND_H

namespace Sounds
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

}  // namespace Sounds
#endif
