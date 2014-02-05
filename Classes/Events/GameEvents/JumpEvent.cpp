#include "JumpEvent.h"

namespace events
{
namespace GameEvents
{
char* Jumpevent::sEventName;

Jumpevent::JumpEvent()
{
}

Jumpevent::~JumpEvent()
{
}

bool Jumpevent::getStartJump()
{
	return 0;
}

void Jumpevent::setStartJump(bool startJump)
{
}
}  // namespace GameEvents
}  // namespace events
