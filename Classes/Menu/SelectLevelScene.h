#ifndef MENU_SELECT_LEVEL_SCENE_H
#define MENU_SELECT_LEVEL_SCENE_H

#include "Physics/EventListenerCustom.h"
#include "Menu/Scene.h"
#include "Menu/GameManager.h"
#include "Menu/EventListenerKeyBoard.h"
#include "Menu/Event.h"

namespace Menu
{
class SelectLevelScene : public Scene
{
private:
	GameManager* _pGameLayer;

	EventListenerKeyBoard* _pKeyEventListener;

	EventListenerCustom* _pDeathEventListener;


protected:
	/**
	 *
	 */
	SelectLevelScene();

	/**
	 * Si le joueur appuie sur Echap -> lancer un OpenTitleScreenEvent
	 */
	void onKeyPress(Event* pEvent);

	/**
	 * Sert à savoir quel niveau est sélectionné.
	 *
	 * Est reçu quand le personnage sort de l'écran alors qu'il a allumé une lumière (sélectionner un niveau)
	 * Regarder quelle lumière est allumée pour savoir quel niveau chargé
	 */
	void onDeathEvent(Event* pEvent);

public:
	~SelectLevelScene();

	static SelectLevelScene* create();

	void init();

};

}  // namespace Menu
#endif
