/*!
 * \file ResetLevelEvent.h
 * \brief Event detecting when the level has to reset
 * \author Xopi
 * \date 13/03/2014
 */
#ifndef EVENTS_GAMEEVENTS_RESET_LEVEL_EVENT_H
#define EVENTS_GAMEEVENTS_RESET_LEVEL_EVENT_H

#include "Events/SynthEvent.h"

namespace events {
/*! \class ResetLevelEvent */
class ResetLevelEvent : public events::SynthEvent {

public:
	static const char* EVENT_NAME;

public:
	ResetLevelEvent();

	~ResetLevelEvent();

};

}  // namespace events
#endif
