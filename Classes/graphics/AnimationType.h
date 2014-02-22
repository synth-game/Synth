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
	IDLE,
	WALK,
	START_JUMP,
	JUMP,
	FALL,
	BOUNCE,
	CRAWL,
	FLY,
	HIT,
	INTERACT,
	COUGH,
	PULL_SWITCH,
	DIE,
	WIN,
	SPAWN,
	BE_HAPPY
} AnimationType;

}  // namespace core
#endif