/*!
 * \file SoundType.h
 * \brief enum for each sound type
 * \author Chupee
 * \date 26/02/2014
 */
#ifndef SOUNDS_SOUND_TYPE_H
#define SOUNDS_SOUND_TYPE_H

namespace sounds {
typedef enum {
	BACKGROUND,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	CYAN,
	MAGENTA,
	WHITE,
	HERO_WALK,
	HERO_IDLE,
	HERO_BOUNCE,
	HERO_COUGH,
	HERO_START_JUMP,
	HERO_FLY,
	FIREFLY_INTERACT,
	FIREFLY_MOVE,
	FIREFLY_OFF,
	FIREFLY_ON,
	LIGHTSWITCH,
} SoundType;

}  // namespace core
#endif