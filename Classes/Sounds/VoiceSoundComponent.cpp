#include "VoiceSoundComponent.h"

namespace Sounds
{

VoiceSoundComponent::VoiceSoundComponent()
{
}

VoiceSoundComponent::~VoiceSoundComponent()
{
}

VoiceSoundComponent* VoiceSoundComponent::create(vector<string> triggeredVoicesTags, vector<string> randomVoicesTags)
{
	return 0;
}

void VoiceSoundComponent::initListeners()
{
}

void VoiceSoundComponent::onVoiceEvent(EventCustom* pEvent)
{
}

void VoiceSoundComponent::update(float fDt)
{
}
}  // namespace Sounds
