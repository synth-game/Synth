#ifndef SOUNDS_LIGHT_SWITCH_SOUND_COMPONENT_H
#define SOUNDS_LIGHT_SWITCH_SOUND_COMPONENT_H



#include "Sounds/SoundComponent.h"

namespace sounds
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

}  // namespace sounds
#endif
