#ifndef EVENTS_GAMEEVENTS_OPEN_TITLE_SCREEN_EVENT_H
#define EVENTS_GAMEEVENTS_OPEN_TITLE_SCREEN_EVENT_H

#include "Events/SynthEvent.h"

namespace events
{
namespace GameEvents
{
class OpenTitleScreenEvent : public Events::SynthEvent
{
public:
	static char* sEventName;


public:
	BackToTitleEvent();

	/**
	 *
	 */
	~BackToTitleEvent();

};

}  // namespace GameEvents
}  // namespace events
#endif
