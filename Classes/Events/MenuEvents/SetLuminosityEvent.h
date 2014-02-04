#ifndef EVENTS_MENUEVENTS_SET_LUMINOSITY_EVENT_H
#define EVENTS_MENUEVENTS_SET_LUMINOSITY_EVENT_H

#include "Events/MenuEvents/SetBoundedParamEvent.h"

namespace Events
{
namespace MenuEvents
{
class SetLuminosityEvent : public SetBoundedParamEvent
{
public:
	static char* sEventName;


public:
	SetLuminosityEvent();

	/**
	 *  
	 */
	~SetLuminosityEvent();

};

}  // namespace MenuEvents
}  // namespace Events
#endif
