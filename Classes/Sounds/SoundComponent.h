/*!
 * \file SoundComponent.h
 * \brief The actor who have this component can make sounds or music
 * \author Chupee
 * \date 27/02/2014
 */
#ifndef SOUNDS_SOUND_COMPONENT_H
#define SOUNDS_SOUND_COMPONENT_H

#include "Core/SynthComponent.h"
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

	inline SoundType getTag() { return _eTag; }
	inline char* getState() { return _sState; }

	inline void setTag(SoundType eTag) { _eTag = eTag; }
	inline void setState(char* sState) { _sState = sState; }

	/*! \brief  Identifies the component */
	static const char* COMPONENT_TYPE;

protected:

	/*! \brief  Constructor */
	SoundComponent();

	/*! \brief  Init listeners */
	void initListeners();

	/**
	 * - Regarde si l'état du owner correspond à un des agglomérat d'état de sa map
	 * - Si c'est le cas, un son doit être joué ! On ajoute le tag du son dans la variable _nextSound si elle est vide.
	 * Quand le son courant (tag dans _currentSound) est fini, on met le son de _nextSound dans _current sound et on le joue. ==> whaaat
	 */
	void onSetStateEvent(EventCustom* pEvent);

	SoundType _eTag;

	char* _sState;

};

}  // namespace sounds
#endif
