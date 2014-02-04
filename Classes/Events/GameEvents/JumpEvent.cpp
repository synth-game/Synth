#include "JumpEvent.h"

namespace Events
{
namespace GameEvents
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
	return 0;
}

void JumpEvent::setStartJump(bool startJump)
{
}
}  // namespace GameEvents
}  // namespace Events
