#include "ChangeNodeOwnerEvent.h"

namespace events
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
	return nullptr;
}

ChangeNodeOwnerEvent::ChangeNodeOwnerEvent()
{
}
}  // namespace GameEvents
}  // namespace events
