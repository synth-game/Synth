#ifndef EVENTS_GAMEEVENTS_COLLISION_EVENT_H
#define EVENTS_GAMEEVENTS_COLLISION_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class CollisionEvent : public Events::SynthEvent
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
}  // namespace Events
#endif
