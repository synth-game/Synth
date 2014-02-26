#ifndef EVENTS_GAMEEVENTS_CHANGE_NODE_OWNER_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_NODE_OWNER_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {


class ChangeNodeOwnerEvent : public events::SynthEvent {
private:
	Node* _newOwner;

public:
	static const char* EVENT_NAME;


public:
	ChangeNodeOwnerEvent();

	~ChangeNodeOwnerEvent();

	Node* _getNewOwner();
};

}  // namespace events
#endif
