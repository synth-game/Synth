#ifndef EVENTS_MENUEVENTS_MAP_KEY_CHANGE_EVENT_H
#define EVENTS_MENUEVENTS_MAP_KEY_CHANGE_EVENT_H

#include "enum.h"
#include "enumGLFW.h"
#include "Events/SynthEvent.h"

namespace Events
{
namespace MenuEvents
{
class MapKeyChangeEvent : public Events::SynthEvent
{
private:
	enum _eBindedAction;

	enumGLFW _eKey;

public:
	static char* sEventName;


public:
	MayKeyChangeEvent();

	/**
	 *  
	 */
	~MayKeyChangeEvent();

	/**
	 *  
	 */
	enum getBindedAction();

	enumGLFW getKey();

	void setBindedAction(enum bindedAction);

	void setKey(enumGLFW key);

};

}  // namespace MenuEvents
}  // namespace Events
#endif
