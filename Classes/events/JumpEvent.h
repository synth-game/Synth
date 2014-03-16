/*!
 * \file JumpEvent.h
 * 
 * \author Flora Jullien
 * \date 19/02/2014
 */
#ifndef EVENTS_GAMEEVENTS_JUMP_EVENT_H
#define EVENTS_GAMEEVENTS_JUMP_EVENT_H

#include "Events/SynthEvent.h"

namespace events {
/*! \class JumpEvent */
class JumpEvent : public events::SynthEvent {

public:
	/*! \brief Constructor */
	JumpEvent(Node* pSource, bool bStartJump);
	JumpEvent(Node* pSource, Point direction, bool bStartJump);
	/*! \brief Destructor */
	~JumpEvent();

	inline bool isStartJumping() { return _bStartJump; }
	inline void setStartJump(bool startJump) { _bStartJump = startJump; }
	inline Point getDirection() { return _direction; }
	inline void setDirection(Point direction) { _direction = direction; }

	static const char* EVENT_NAME;

private:
	bool _bStartJump;
	Point _direction;
};

}  // namespace events
#endif
