#include "VoiceEvent.h"

namespace events
{
namespace GameEvents
{
char* Voiceevent::sEventName;

Voiceevent::VoiceEvent()
{
}

Voiceevent::~VoiceEvent()
{
}

bool Voiceevent::isTriggeredVoice()
{
	return 0;
}

void Voiceevent::setTriggeredVoice(bool bIsTriggeredVoice)
{
}
}  // namespace GameEvents
}  // namespace events
