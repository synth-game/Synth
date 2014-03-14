/*!
 * \file LightSwitchSoundComponent.h
 * \brief The lightswitch can make sounds
 * \author Chupee
 * \date 14/03/2014
 */
#ifndef SOUNDS_LIGHT_SWITCH_SOUND_COMPONENT_H
#define SOUNDS_LIGHT_SWITCH_SOUND_COMPONENT_H


#include "Sounds/SoundComponent.h"

namespace sounds {

class LightSwitchSoundComponent : public SoundComponent {

public:

	~LightSwitchSoundComponent();

	static LightSwitchSoundComponent* create();

	void onToggleLight(EventCustom* pEvent);

protected:

	LightSwitchSoundComponent();

	void initListeners();

private:

	EventListenerCustom* _pToggleLightEventListener;


};

}  // namespace sounds
#endif
