#ifndef SOUNDS_LIGHT_SWITCH_SOUND_COMPONENT_H
#define SOUNDS_LIGHT_SWITCH_SOUND_COMPONENT_H

#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Sounds/SoundComponent.h"

namespace Sounds
{
class LightSwitchSoundComponent : public SoundComponent
{
private:
	EventListenerCustom* _pToggleLightEventListener;


protected:
	/**
	 *
	 */
	LightSwitchSoundComponent();

public:
	/**
	 *
	 */
	~LightSwitchSoundComponent();

	static LightSwitchSoundComponent* create();

	void onToggleLight(EventCustom* pEvent);

};

}  // namespace Sounds
#endif
