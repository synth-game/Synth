/*!
 * \file FireflySoundComponent.h
 * \brief Fireflies can make sounds !
 * \author Chupee
 * \date 13/03/2014
 */
#ifndef SOUNDS_FIREFLY_SOUND_COMPONENT_H
#define SOUNDS_FIREFLY_SOUND_COMPONENT_H



#include "Sounds/SoundComponent.h"

namespace sounds {
	
/*! \class FireflySoundComponent.h
 * \brief Fireflies can make sounds !
 *
 * 
 */
class FireflySoundComponent : public SoundComponent {

public:
	~FireflySoundComponent();

	static FireflySoundComponent* create();

	void onChangePosition(EventCustom* pEvent);

	void onToggleLight(EventCustom* pEvent);

	void onChangeNodeOwner(EventCustom* pEvent);

protected:
	FireflySoundComponent();

	void initListeners();

private:
	EventListenerCustom* _pChangePositionEventListener;

	EventListenerCustom* _pToggleLightEventListener;

	EventListenerCustom* _pChangeNodeOwnerEventListener;




};

}  // namespace sounds
#endif
