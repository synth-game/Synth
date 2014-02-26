#ifndef EVENTS_MENUEVENTS_SET_BOUNDED_PARAM_EVENT_H
#define EVENTS_MENUEVENTS_SET_BOUNDED_PARAM_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace MenuEvents
{
class SetBoundedParamEvent : public events::SynthEvent
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
}  // namespace events
#endif
