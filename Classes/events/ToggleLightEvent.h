/*!
 * \file ToggleLightEvent.h
 * \brief Event that turns on/off a light
 * \author Chupee
 * \date 26/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H
#define EVENTS_GAMEEVENTS_TOGGLE_LIGHT_EVENT_H

#include "core/SynthActor.h"
#include "Events/SynthEvent.h"

namespace events {

class ToggleLightEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	ToggleLightEvent(Node* pSource, core::SynthActor* pTarget, bool bOn);

	/*! \brief Destructor */
	~ToggleLightEvent();

	/*! \brief Are we turning the light on or off ? */
	inline bool isOn() { return _bOn; };

	/*! \brief Choose to turn the light on or off */
	inline void setOn(bool bOn) { _bOn = bOn; };

	inline core::SynthActor* getTarget() { return _pTarget; };

	inline void setTarget(core::SynthActor* pTarget) { _pTarget = pTarget; };

private:

	/*! \brief Boolean that says if we turn the light on or off */
	bool _bOn;

	core::SynthActor* _pTarget;

public:

	/*! \brief Identifies the event */
	static const char* EVENT_NAME;

};

}  // namespace events
#endif
