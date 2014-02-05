#include "JumpEvent.h"

namespace events
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
	return false;
}

void JumpEvent::setStartJump(bool startJump)
{
}
}  // namespace GameEvents
}  // namespace events
