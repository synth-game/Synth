#ifndef EVENTS_MENUEVENTS_MAP_KEY_CHANGE_EVENT_H
#define EVENTS_MENUEVENTS_MAP_KEY_CHANGE_EVENT_H

#include "system/BindedAction.h"
#include "Events/SynthEvent.h"

namespace events
{
namespace MenuEvents
{
class MapKeyChangeEvent : public events::SynthEvent
{
private:
	synthsystem::BindedAction _eBindedAction;

	int _eKey; //TO CHANGE

public:
	static char* sEventName;


public:
	MapKeyChangeEvent();

	/**
	 *
	 */
	~MapKeyChangeEvent();

	/**
	 *
	 */
	synthsystem::BindedAction getBindedAction();

	int getKey();

	void setBindedAction(synthsystem::BindedAction bindedAction);

	void setKey(int key);

};

}  // namespace MenuEvents
}  // namespace events
#endif
