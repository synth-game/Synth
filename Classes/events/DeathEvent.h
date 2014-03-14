/*!
 * \file DeathEvent.h
 * \brief Event detecting when the players dies
 * \author Xopi
 * \date 12/03/2014
 */
#ifndef EVENTS_GAMEEVENTS_DEATH_EVENT_H
#define EVENTS_GAMEEVENTS_DEATH_EVENT_H

#include "Events/SynthEvent.h"

namespace events {
/*! \class DeathEvent */
class DeathEvent : public events::SynthEvent {
public:
	static const char* EVENT_NAME;


public:
	DeathEvent();

	~DeathEvent();

};

}  // namespace events
#endif
