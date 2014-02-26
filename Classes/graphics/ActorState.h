/*!
 * \file ActorState.h
 * \brief enum for the state of the Actor.
 * \author Chupee
 * \date 22/02/2014
 */
#ifndef GRAPHICS_ACTOR_STATE_H
#define GRAPHICS_ACTOR_STATE_H

namespace graphics {
typedef enum {
	IDLE_STATE,
	ON_FLOOR_STATE,
	ON_AIR_STATE,
	BOUNCE_STATE,
	STUCK_STATE
} ActorState;

}  // namespace core
#endif