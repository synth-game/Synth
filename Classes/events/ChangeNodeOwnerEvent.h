/*!
 * \file ChangeNodeOwnerEvent.h
 * \brief Event that announce that an actor changes its owner.
 * \author Chupee
 * \date 26/02/2014
 */

#ifndef EVENTS_GAMEEVENTS_CHANGE_NODE_OWNER_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_NODE_OWNER_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {

/*! \class ChangeNodeOwnerEvent
 * \brief Event that announce that an actor changes its owner.
 *
 */
class ChangeNodeOwnerEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	ChangeNodeOwnerEvent();

	/*! \brief Destructor */
	~ChangeNodeOwnerEvent();

	/*! \brief Get the new owner */
	inline Node* getNewOwner() { return _newOwner; };

public:
	/*! \brief Identifies the event */
	static const char* EVENT_NAME;

private:
	/*! \brief The new owner of the actor */
	Node* _newOwner;

};

}  // namespace events
#endif
