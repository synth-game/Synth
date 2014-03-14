/*!
 * \file SoundComponent.h
 * \brief The actor who have this component can make sounds or music
 * \author Chupee
 * \date 27/02/2014
 */
#ifndef SOUNDS_SOUND_COMPONENT_H
#define SOUNDS_SOUND_COMPONENT_H

#include "Core/SynthComponent.h"
#include "core/ActorState.h"
#include "sounds/SoundType.h"

namespace sounds {

/*! \class SoundComponent
 * \brief The actor who have this component can make sounds or music
 *
 * 
 */
class SoundComponent : public core::SynthComponent {

public:

	/*! \brief Destructor */
	~SoundComponent();

	bool init();

	/*! \brief Create the component */
	static SoundComponent* create();

	inline SoundType getCurrentTag() { return _eCurrentTag; }
	inline core::ActorState getState() { return _eState; }

	inline void setCurrentTag(SoundType eTag) { _eCurrentTag = eTag; }
	inline core::ActorState setState(core::ActorState eState) { _eState = eState; }

	void playSound( SoundType type );

	void stopSounds();

	/*! \brief  Identifies the component */
	static const char* COMPONENT_TYPE;

	void onChangeState(EventCustom* pEvent);

protected:

	/*! \brief  Constructor */
	SoundComponent();

	/*! \brief  Init listeners */
	void initListeners();

	

	SoundType _eCurrentTag;

	core::ActorState _eState;

	EventListenerCustom* _pChangeStateEventListener;

};

}  // namespace sounds
#endif
