#include "MapKeyChangeEvent.h"

namespace events
{
namespace MenuEvents
{
char* MapKeyChangeEvent::sEventName;

MapKeyChangeEvent::MayKeyChangeEvent()
{
}

MapKeyChangeEvent::~MayKeyChangeEvent()
{
}

enum MapKeyChangeEvent::getBindedAction()
{
	return 0;
}

enumGLFW MapKeyChangeEvent::getKey()
{
	return 0;
}

void MapKeyChangeEvent::setBindedAction(enum bindedAction)
{
}

void MapKeyChangeEvent::setKey(enumGLFW key)
{
}
}  // namespace MenuEvents
}  // namespace events
