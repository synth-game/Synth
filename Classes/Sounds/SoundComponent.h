#ifndef SOUNDS_SOUND_COMPONENT_H
#define SOUNDS_SOUND_COMPONENT_H

#include "Component.h"

#include "Core/SynthComponent.h"

namespace sounds
{
class SoundComponent : public Component, public core::SynthComponent
{
protected:
	int _iTrackID;

	char* _state;

public:
	static char* COMPONENT_TYPE;


protected:
	/**
	 *
	 */
	SoundComponent();

public:
	/**
	 *
	 */
	~SoundComponent();

	/**
	 * - Regarde si l'état du owner correspond à un des agglomérat d'état de sa map
	 * - Si c'est le cas, un son doit être joué ! On ajoute le tag du son dans la variable _nextSound si elle est vide.
	 * Quand le son courant (tag dans _currentSound) est fini, on met le son de _nextSound dans _current sound et on le joue.
	 */
	void onSetStateEvent(EventCustom* pEvent);

	/**
	 *
	 */
	bool init();

};

}  // namespace sounds
#endif
