#include "MapKeyChangeEvent.h"

namespace events
{
namespace MenuEvents
{
char* MapKeyChangeEvent::sEventName;

MapKeyChangeEvent::MapKeyChangeEvent()
{
}

MapKeyChangeEvent::~MapKeyChangeEvent()
{
}

synthsystem::BindedAction MapKeyChangeEvent::getBindedAction()
{
	return synthsystem::NO_ACTION;
}

int MapKeyChangeEvent::getKey()
{
	return 0;
}

void MapKeyChangeEvent::setBindedAction(synthsystem::BindedAction bindedAction)
{
}

void MapKeyChangeEvent::setKey(int key)
{
}
}  // namespace MenuEvents
}  // namespace events
