/*!
 * \file InterruptMoveEvent.h
 * 
 * \author Flora Jullien
 * \date 19/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_INTERRUPT_MOVE_EVENT_H
#define EVENTS_GAMEEVENTS_INTERRUPT_MOVE_EVENT_H

#include "Events/SynthEvent.h"

namespace events {
/*! \class InterruptMoveEvent */
class InterruptMoveEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	InterruptMoveEvent();
	/*! \brief Destructor */
	~InterruptMoveEvent();

	inline bool getStopX() { return _bStopX; }
	inline bool getStopY() { return _bStopY; }
	inline bool getHasMoved() { return _bHasMoved; }
	inline void setStopX(bool stopX) { _bStopX = stopX; }
	inline void setStopY(bool stopY) { _bStopY = stopY; }
	inline bool setHasMoved() { _bHasMoved = true; }

	static const char* EVENT_NAME;

private:
	bool _bStopX;
	bool _bStopY;
	bool _bHasMoved;
};

}  // namespace events
#endif
