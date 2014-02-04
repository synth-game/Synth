#ifndef SOUNDS_FIREFLY_SOUND_COMPONENT_H
#define SOUNDS_FIREFLY_SOUND_COMPONENT_H

#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Sounds/SoundComponent.h"

namespace Sounds
{
class FireflySoundComponent : public SoundComponent
{
private:
	Physics::EventListenerCustom* _pChangePositionEventListener;

	Physics::EventListenerCustom* _pToggleLightEventListener;

	Physics::EventListenerCustom* _pNodeOwnerChangeEventListener;


protected:
	FireflySoundComponent();

	void initListeners();

public:
	~FireflySoundComponent();

	static FireflySoundComponent* create();

	void onChangePosition(EventCustom* pEvent);

	void onToggleLight(EventCustom* pEvent);

	void onNodeOwnerChange(EventCustom* pEvent);

};

}  // namespace Sounds
#endif
