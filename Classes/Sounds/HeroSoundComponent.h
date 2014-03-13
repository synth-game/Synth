/*!
 * \file HeroSoundComponent.h
 * \brief The hero can make sounds !
 * \author Chupee
 * \date 13/03/2014
 */

#ifndef SOUNDS_HERO_SOUND_COMPONENT_H
#define SOUNDS_HERO_SOUND_COMPONENT_H



#include "Sounds/SoundComponent.h"

namespace sounds {

/*! \class HeroSoundComponent
 * \brief The hero can make sounds !
 *
 * 
 */
class HeroSoundComponent : public SoundComponent {
	
public:
	~HeroSoundComponent();

	static HeroSoundComponent* create();

	void onChangePosition(EventCustom* pEvent);

	void onJump(EventCustom* pEvent);

	void onEditMove(EventCustom* pEvent);

	void onInterruptMove(EventCustom* pEvent);

	void onHeroDeath(EventCustom* pEvent);

	void onPeriodicEvent(EventCustom* pEvent);


protected:
	HeroSoundComponent();

	void initListeners();

private:
	EventListenerCustom* _pChangePositionEventListener;

	EventListenerCustom* _pJumpEventListener;

	EventListenerCustom* _pInterruptMoveEventListener;

	EventListenerCustom* _pHeroDeathEventListener;

	EventListenerCustom* _pPeriodicEventListener;

	EventListenerCustom* _pEditMoveEventListener;




};

}  // namespace sounds
#endif
