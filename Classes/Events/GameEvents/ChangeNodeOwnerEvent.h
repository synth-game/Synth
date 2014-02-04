#ifndef EVENTS_GAMEEVENTS_CHANGE_NODE_OWNER_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_NODE_OWNER_EVENT_H

#include "Node.h"
#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class ChangeNodeOwnerEvent : public Events::SynthEvent
{
private:
	Node* _newOwner;

public:
	static char* sEventName;


public:
	ChangeNodeOwnerEvent();

	~ChangeNodeOwnerEvent();

	Node* _getNewOwner();

	ChangeNodeOwnerEvent();

};

}  // namespace GameEvents
}  // namespace Events
#endif
