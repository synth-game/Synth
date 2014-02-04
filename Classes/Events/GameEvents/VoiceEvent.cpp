#include "VoiceEvent.h"

namespace Events
{
namespace GameEvents
{
char* VoiceEvent::sEventName;

VoiceEvent::VoiceEvent()
{
}

VoiceEvent::~VoiceEvent()
{
}

boolean VoiceEvent::isTriggeredVoice()
{
	return 0;
}

void VoiceEvent::setTriggeredVoice(boolean bIsTriggeredVoice)
{
}
}  // namespace GameEvents
}  // namespace Events
