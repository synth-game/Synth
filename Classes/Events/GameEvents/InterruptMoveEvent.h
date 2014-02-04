#ifndef EVENTS_GAMEEVENTS_INTERRUPT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_INTERRUPT_MOVE_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class InterruptMoveEvent : public Events::SynthEvent
{
private:
	boolean _bStopX;

	boolean _bStopY;

	boolean _bHasMoved;

public:
	static char* sEventName;


public:
	InterruptMoveEvent();

	/**
	 *  
	 */
	~InterruptMoveEvent();

	boolean getStopX();

	boolean getStopY();

	boolean getHasMoved();

	void setStopX(boolean stopX);

	void setStopY(boolean stopY);

	boolean setHasMoved();

};

}  // namespace GameEvents
}  // namespace Events
#endif
