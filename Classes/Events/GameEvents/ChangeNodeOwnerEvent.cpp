#include "ChangeNodeOwnerEvent.h"

namespace Events
{
namespace GameEvents
{
char* ChangeNodeOwnerEvent::sEventName;

ChangeNodeOwnerEvent::ChangeNodeOwnerEvent()
{
}

ChangeNodeOwnerEvent::~ChangeNodeOwnerEvent()
{
}

Node* ChangeNodeOwnerEvent::_getNewOwner()
{
	return 0;
}

ChangeNodeOwnerEvent::ChangeNodeOwnerEvent()
{
}
}  // namespace GameEvents
}  // namespace Events
