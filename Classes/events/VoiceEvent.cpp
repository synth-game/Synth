#include "VoiceEvent.h"

namespace events
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
}  // namespace events
