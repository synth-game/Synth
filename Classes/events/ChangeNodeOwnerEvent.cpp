#include "ChangeNodeOwnerEvent.h"

namespace events
{
namespace GameEvents
{
char* ChangeNodeOwnerevent::sEventName;

ChangeNodeOwnerevent::ChangeNodeOwnerEvent()
{
}

ChangeNodeOwnerevent::~ChangeNodeOwnerEvent()
{
}

Node* ChangeNodeOwnerevent::_getNewOwner()
{
	return 0;
}

ChangeNodeOwnerevent::ChangeNodeOwnerEvent()
{
}
}  // namespace GameEvents
}  // namespace events
