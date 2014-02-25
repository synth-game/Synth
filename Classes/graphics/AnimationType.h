/*!
 * \file AnimationType.h
 * \brief enum for each animation type
 * \author Chupee
 * \date 22/02/2014
 */
#ifndef GRAPHICS_ANIMATION_TYPE_H
#define GRAPHICS_ANIMATION_TYPE_H

namespace graphics {
typedef enum {
	HERO_IDLE,
	HERO_WALK,
	HERO_START_JUMP,
	HERO_JUMP,
	HERO_FALL,
	HERO_BOUNCE,
	HERO_CRAWL,
	HERO_FLY,
	HERO_HIT,
	HERO_INTERACT,
	HERO_COUGH,
	HERO_PULL_SWITCH,
	HERO_DIE,
	HERO_WIN,
	HERO_SPAWN,
	FIREFLY_IDLE,
	FIREFLY_BE_HAPPY
} AnimationType;

}  // namespace core
#endif