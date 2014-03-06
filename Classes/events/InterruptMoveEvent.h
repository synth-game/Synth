/*!
 * \file InterruptMoveEvent.h
 * \brief Event send to completly stop actor velocity
 * \author Flora Jullien
 * \date 19/02/2014
 */
#ifndef EVENTS_INTERRUPT_MOVE_EVENT_H
#define EVENTS_INTERRUPT_MOVE_EVENT_H

#include "cocos2d.h"
#include "Events/SynthEvent.h"

USING_NS_CC;

namespace events {
/*! \class InterruptMoveEvent
 * \brief Event send to completly stop actor velocity
 */
class InterruptMoveEvent : public SynthEvent {

public:
	/*! \brief Constructor */
	InterruptMoveEvent(Node* pSource, bool bStopX, bool bStopY, bool bHasMoved);
	/*! \brief Destructor */
	~InterruptMoveEvent();

	inline bool getStopX() { return _bStopX; }
	inline bool getStopY() { return _bStopY; }
	inline bool getHasMoved() { return _bHasMoved; }
	inline void setStopX(bool stopX) { _bStopX = stopX; }
	inline void setStopY(bool stopY) { _bStopY = stopY; }
	inline void setHasMoved() { _bHasMoved = true; }

	static const char* EVENT_NAME;

private:
	bool _bStopX;
	bool _bStopY;
	bool _bHasMoved;
};

}  // namespace events
#endif //EVENTS_INTERRUPT_MOVE_EVENT_H
