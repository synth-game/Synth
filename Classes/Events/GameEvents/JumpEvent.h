#ifndef EVENTS_GAMEEVENTS_JUMP_EVENT_H
#define EVENTS_GAMEEVENTS_JUMP_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace GameEvents
{
class JumpEvent : public Events::SynthEvent
{
private:
	boolean _bStartJump;

public:
	static char* sEventName;


public:
	JumpEvent();

	/**
	 *  
	 */
	~JumpEvent();

	boolean getStartJump();

	void setStartJump(boolean startJump);

};

}  // namespace GameEvents
}  // namespace Events
#endif
