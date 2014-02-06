#ifndef EVENTS_MENUEVENTS_SET_LANGUAGE_EVENT_H
#define EVENTS_MENUEVENTS_SET_LANGUAGE_EVENT_H

#include "Events/SynthEvent.h"
#include "core/Language.h"

namespace events
{
namespace MenuEvents
{
class SetLanguageEvent : public events::SynthEvent
{
private:
	core::Language eLanguage;


public:
	SetLanguageEvent();

	/**
	 *
	 */
	~SetLanguageEvent();

	core::Language getLanguage();

	void setLanguage(core::Language language);

};

}  // namespace MenuEvents
}  // namespace events
#endif
