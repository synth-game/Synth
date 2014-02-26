/*!
 * \file ToggleLightEvent.h
 * \brief Event that turns on/off a light
 * \author Chupee
 * \date 26/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H
#define EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H

#include "Events/SynthEvent.h"

namespace events {

class ToggleLightEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	ToggleLightEvent();

	/*! \brief Destructor */
	~ToggleLightEvent();

	/*! \brief Are we turning the light on or off ? */
	inline bool isOn() { return _bOn; };

	/*! \brief Choose to turn the light on or off */
	inline void setOn(bool bOn) { _bOn = bOn; };

private:

	/*! \brief Boolean that says if we turn the light on or off */
	bool _bOn;

public:

	/*! \brief Identifies the event */
	static const char* EVENT_NAME;

};

}  // namespace events
#endif
