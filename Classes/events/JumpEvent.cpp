#include "JumpEvent.h"

namespace events
{

char* JumpEvent::sEventName;

JumpEvent::JumpEvent()
{
}

JumpEvent::~JumpEvent()
{
}

bool JumpEvent::getStartJump()
{
	return false;
}

void JumpEvent::setStartJump(bool startJump)
{
}

}  // namespace events
