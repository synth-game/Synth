#ifndef EVENTS_GAMEEVENTS_COLLISION_EVENT_H
#define EVENTS_GAMEEVENTS_COLLISION_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class CollisionEvent : public events::SynthEvent
{
public:
	static char* sEventName;


public:
	CollisionEvent();

	/**
	 *
	 */
	~CollisionEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
