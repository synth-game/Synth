/*!
 * \file ActorType.h
 * \brief enum for each actor type
 * \author Jijidici
 * \date 20/02/2014
 */
#ifndef CORE_ACTOR_TYPE_H
#define CORE_ACTOR_TYPE_H

namespace core {
typedef enum {
	UNKNOWN_TYPE,
	HERO,
	BLUE_FIREFLY,
	RED_FIREFLY,
	GREEN_FIREFLY,
	LIGHT,
	LIGHTSWITCH,
	ACTORTYPE_COUNT
} ActorType;

}  // namespace core
#endif
