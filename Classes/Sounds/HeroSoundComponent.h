#ifndef SOUNDS_HERO_SOUND_COMPONENT_H
#define SOUNDS_HERO_SOUND_COMPONENT_H



#include "Sounds/SoundComponent.h"

namespace sounds
{
class HeroSoundComponent : public SoundComponent
{
private:
	EventListenerCustom* _pChangePositionEventListener;

	EventListenerCustom* _pJumpEventListener;

	EventListenerCustom* _pInterruptMoveEventListener;

	EventListenerCustom* _pHeroDeathEventListener;

	EventListenerCustom* _pPeriodicEventListener;


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

}  // namespace sounds
#endif
