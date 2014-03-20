/*!
 * \file ActorState.h
 * \brief enum for the state of the Actor.
 * \author Chupee
 * \date 22/02/2014
 */
#ifndef CORE_ACTOR_STATE_H
#define CORE_ACTOR_STATE_H

namespace core {
typedef enum {
	NO_STATE,
	IDLE_STATE,
	ON_FLOOR_STATE,
	ON_AIR_STATE,
	BOUNCE_STATE,
	STUCK_STATE,
    STUCK_TOP_STATE,
    STUCK_BOTTOM_STATE,
    STUCK_LEFT_STATE,
    STUCK_RIGHT_STATE,
	NOT_ON_FLOOR_STATE
} ActorState;

}  // namespace core
#endif