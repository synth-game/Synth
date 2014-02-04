#ifndef SOUNDS_HERO_SOUND_COMPONENT_H
#define SOUNDS_HERO_SOUND_COMPONENT_H

#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Sounds/SoundComponent.h"

namespace Sounds
{
class HeroSoundComponent : public SoundComponent
{
private:
	Physics::EventListenerCustom* _pChangePositionEventListener;

	Physics::EventListenerCustom* _pJumpEventListener;

	Physics::EventListenerCustom* _pInterruptMoveEventListener;

	Physics::EventListenerCustom* _pHeroDeathEventListener;

	Physics::EventListenerCustom* _pPeriodicEventListener;


protected:
	HeroSoundComponent();

	void initListeners();

public:
	~HeroSoundComponent();

	static HeroSoundComponent* create();

	void onChangePosition(EventCustom* pEvent);

	void onJump(EventCustom* pEvent);

	void onInterruptMove(EventCustom* pEvent);

	void onHeroDeath(EventCustom* pEvent);

	void onPeriodicEvent(EventCustom* pEvent);

};

}  // namespace Sounds
#endif
