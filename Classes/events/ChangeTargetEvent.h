/*!
 * \file ChangeTargetEvent.h
 * \brief Change the target of the follow movement
 * \author Chupee
 * \date 04/03/2014
 */
#ifndef EVENTS_GAMEEVENTS_CHANGE_TARGET_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_TARGET_EVENT_H

#include "cocos2d.h"
#include "core/SynthActor.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {

class ChangeTargetEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	ChangeTargetEvent(Node* pSource, core::SynthActor* newTarget);

	/*! \brief Destructor */
	~ChangeTargetEvent();

	inline core::SynthActor* getNewTarget() { return _newTarget; }
	inline void setNewTarget(core::SynthActor* newTarget) { _newTarget = newTarget; }

	static const char* EVENT_NAME;

private:
	core::SynthActor* _newTarget;





};

}  // namespace events
#endif
