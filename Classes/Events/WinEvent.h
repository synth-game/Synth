/*!
 * \file WinEvent.h
 * \brief Event detecting when the players wins a level
 * \author Xopi
 * \date 09/03/2014
 */
#ifndef EVENTS_GAMEEVENTS_WIN_EVENT_H
#define EVENTS_GAMEEVENTS_WIN_EVENT_H

#include "Events/SynthEvent.h"

namespace events {
/*! \class WinEvent */
class WinEvent : public events::SynthEvent {
public:
	static const char* EVENT_NAME;

public:
	WinEvent();

	~WinEvent();

};

}  // namespace events
#endif
