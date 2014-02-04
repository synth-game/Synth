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

bool VoiceEvent::isTriggeredVoice()
{
	return 0;
}

void VoiceEvent::setTriggeredVoice(bool bIsTriggeredVoice)
{
}
}  // namespace GameEvents
}  // namespace Events
