#ifndef EVENTS_GAMEEVENTS_JUMP_EVENT_H
#define EVENTS_GAMEEVENTS_JUMP_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class JumpEvent : public Events::SynthEvent
{
private:
	bool _bStartJump;

public:
	static char* sEventName;


public:
	JumpEvent();

	/**
	 *
	 */
	~JumpEvent();

	bool getStartJump();

	void setStartJump(bool startJump);

};

}  // namespace GameEvents
}  // namespace events
#endif
