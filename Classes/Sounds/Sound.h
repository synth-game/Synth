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
	std::string filePath;

	bool bLoop;

	std::string chainedSoundName;

};

}  // namespace sounds
#endif
