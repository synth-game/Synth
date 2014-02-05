#include "VoiceSoundComponent.h"

namespace sounds
{

VoiceSoundComponent::VoiceSoundComponent()
{
}

VoiceSoundComponent::~VoiceSoundComponent()
{
}

VoiceSoundComponent* VoiceSoundComponent::create(std::vector<std::string> triggeredVoicesTags, std::vector<std::string> randomVoicesTags)
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
}  // namespace sounds
