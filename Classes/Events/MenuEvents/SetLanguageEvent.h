#ifndef EVENTS_MENUEVENTS_SET_LANGUAGE_EVENT_H
#define EVENTS_MENUEVENTS_SET_LANGUAGE_EVENT_H

#include "Events/SynthEvent.h"
#include "Events/MenuEvents/Language.h"

namespace Events
{
namespace MenuEvents
{
class SetLanguageEvent : public Events::SynthEvent
{
private:
	Language eLanguage;


public:
	SetLanguageEvent();

	/**
	 *  
	 */
	~SetLanguageEvent();

	Language getLanguage();

	void setLanguage(Language language);

};

}  // namespace MenuEvents
}  // namespace Events
#endif
