#ifndef EVENTS_SCREENEVENTS_LOAD_SELECTED_LEVEL_EVENT_H
#define EVENTS_SCREENEVENTS_LOAD_SELECTED_LEVEL_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace ScreenEvents
{
class LoadSelectedLevelEvent : public Events::SynthEvent
{
private:
	int _iLevel;

public:
	static char* sEventName;


public:
	LoadSelectedLevelEvent();

	/**
	 *
	 */
	~LoadSelectedLevelEvent();

	int getLevel();

	void setLevel(int level);

};

}  // namespace ScreenEvents
}  // namespace events
#endif
