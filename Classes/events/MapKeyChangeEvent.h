#ifndef EVENTS_MENUEVENTS_MAP_KEY_CHANGE_EVENT_H
#define EVENTS_MENUEVENTS_MAP_KEY_CHANGE_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace MenuEvents
{
class MapKeyChangeEvent : public events::SynthEvent
{
private:
	enum _eBindedAction;

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
	int getBindedAction();

	int getKey();

	void setBindedAction(enum bindedAction);

	void setKey(int key);

};

}  // namespace MenuEvents
}  // namespace events
#endif
