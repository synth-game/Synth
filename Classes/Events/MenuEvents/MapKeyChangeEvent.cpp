#include "MapKeyChangeEvent.h"

namespace events
{
namespace MenuEvents
{
char* MapKeyChangeevent::sEventName;

MapKeyChangeevent::MayKeyChangeEvent()
{
}

MapKeyChangeevent::~MayKeyChangeEvent()
{
}

enum MapKeyChangeevent::getBindedAction()
{
	return 0;
}

enumGLFW MapKeyChangeevent::getKey()
{
	return 0;
}

void MapKeyChangeevent::setBindedAction(enum bindedAction)
{
}

void MapKeyChangeevent::setKey(enumGLFW key)
{
}
}  // namespace MenuEvents
}  // namespace events
