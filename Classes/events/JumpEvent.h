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
	/*! \brief Destructor */
	~JumpEvent();

	inline bool isStartJumping() { return _bStartJump; }
	void setStartJump(bool startJump) { _bStartJump = startJump; }

	static const char* EVENT_NAME;

private:
	bool _bStartJump;
};

}  // namespace events
#endif
