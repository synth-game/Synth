#ifndef SOUNDS_VOICE_SOUND_COMPONENT_H
#define SOUNDS_VOICE_SOUND_COMPONENT_H

#include <vector>
#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Sounds/SoundComponent.h"

namespace Sounds
{
class VoiceSoundComponent : public SoundComponent
{
private:
	EventListenerCustom* _pVoiceEventListener;

	/**
	 * contient les tags de voix declenchées en passant sur des triggers spaciaux. les tags sont envoyés au soundmanager pour être lus.
	 */
	vector<string> _triggeredVoicesTags;

	/**
	 * contient les tags de voix declenchées en passant sur des triggers spaciaux. les tags sont envoyés au soundmanager pour être lus.
	 */
	vector<string> _randomVoicesTags;

	int _iCurrentTriggeredVoice;


protected:
	VoiceSoundComponent();

	void initListeners();

public:
	/**
	 *
	 */
	~VoiceSoundComponent();

	static VoiceSoundComponent* create(vector<string> triggeredVoicesTags, vector<string> randomVoicesTags);

	/**
	 * récupére un event de voix random ou voix triggered, comprotement différent selon si c'est random ou triggered. On parcourt la liste des voix dans l'ordre de la liste.
	 * Lance en meme temps un event ToggleTextEvent avec le tag correspondant si soustitres activés.
	 * Si c'est trigerred, ne pas oublier d'incrémenter le curseur iCurrentTriggeredVoice
	 *
	 *
	 */
	void onVoiceEvent(EventCustom* pEvent);

	/**
	 * Vérifier à chaque frame si le son est fini avec SoundManager::isFinished()
	 *  - si c'est le cas, lancer un ToggleTextEvent (avec bOn=false)
	 */
	void update(float fDt);

};

}  // namespace Sounds
#endif