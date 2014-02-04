#ifndef EVENTS_MENUEVENTS_SET_BOUNDED_PARAM_EVENT_H
#define EVENTS_MENUEVENTS_SET_BOUNDED_PARAM_EVENT_H

#include "Events/SynthEvent.h"

namespace Events
{
namespace MenuEvents
{
class SetBoundedParamEvent : public Events::SynthEvent
{
private:
	float fParam;


public:
	SetBoundedParamEvent();

	/**
	 *  
	 */
	~SetBoundedParamEvent();

	float getParam();

	void setParam(float param);

};

}  // namespace MenuEvents
}  // namespace Events
#endif
