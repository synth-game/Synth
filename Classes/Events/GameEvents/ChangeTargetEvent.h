#ifndef EVENTS_GAMEEVENTS_CHANGE_TARGET_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_TARGET_EVENT_H

#include "Events/Point.h"

namespace events
{
namespace GameEvents
{
class ChangeTargetEvent
{
private:
	Events::Point newTarget;

public:
	static char* sEventName;


public:
	ChangeTargetEvent();

	/**
	 *
	 */
	~ChangeTargetEvent();

	Events::Point getNewTarget();

	void setNewTarget(Events::Point newTarget);

};

}  // namespace GameEvents
}  // namespace events
#endif
