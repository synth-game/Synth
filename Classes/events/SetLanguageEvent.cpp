#include "SetLanguageEvent.h"

namespace events
{
namespace MenuEvents
{

SetLanguageEvent::SetLanguageEvent()
{
}

SetLanguageEvent::~SetLanguageEvent()
{
}

core::Language SetLanguageEvent::getLanguage()
{
	return core::FRENCH;
}

void SetLanguageEvent::setLanguage(core::Language language)
{
}
}  // namespace MenuEvents
}  // namespace events
