#ifndef EVENTS_GAMEEVENTS_INTERRUPT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_INTERRUPT_MOVE_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class InterruptMoveEvent : public events::SynthEvent
{
private:
	bool _bStopX;

	bool _bStopY;

	bool _bHasMoved;

public:
	static char* sEventName;


public:
	InterruptMoveEvent();

	/**
	 *
	 */
	~InterruptMoveEvent();

	bool getStopX();

	bool getStopY();

	bool getHasMoved();

	void setStopX(bool stopX);

	void setStopY(bool stopY);

	bool setHasMoved();

};

}  // namespace GameEvents
}  // namespace events
#endif
