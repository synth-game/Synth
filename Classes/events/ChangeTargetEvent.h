#ifndef EVENTS_GAMEEVENTS_CHANGE_TARGET_EVENT_H
#define EVENTS_GAMEEVENTS_CHANGE_TARGET_EVENT_H

#include "cocos2d.h"

USING_NS_CC;

namespace events
{
namespace GameEvents
{
class ChangeTargetEvent
{
private:
	Point newTarget;

public:
	static char* sEventName;


public:
	ChangeTargetEvent();

	/**
	 *
	 */
	~ChangeTargetEvent();

	Point getNewTarget();

	void setNewTarget(Point newTarget);

};

}  // namespace GameEvents
}  // namespace events
#endif
