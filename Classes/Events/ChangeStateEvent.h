/*!
 * \file ChangeStateEvent.cpp
 * \brief Changes the state of the actor for the animation
 * \author Chupee
 * \date 25/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_CHANGE_STATE_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_STATE_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"
#include "core/ActorState.h"

USING_NS_CC;

namespace events {

class ChangeStateEvent : public events::SynthEvent {

public:

	ChangeStateEvent(Node* pSource, core::ActorState eState);

	~ChangeStateEvent();

	static const char* EVENT_NAME;

	inline core::ActorState getNewState() { return _eNewState; }

	inline void setNewState(core::ActorState eNewState) { _eNewState = eNewState; }

private:
	core::ActorState _eNewState;

};

}  // namespace events
#endif
