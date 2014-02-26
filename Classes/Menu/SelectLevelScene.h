#ifndef MENU_SELECT_LEVEL_SCENE_H
#define MENU_SELECT_LEVEL_SCENE_H

#include "cocos2d.h"
#include "game/GameManager.h"

USING_NS_CC;

namespace menu
{
class SelectLevelScene : public Scene
{
private:
	game::GameManager* _pGameLayer;

	EventListenerKeyboard* _pKeyEventListener;

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

	bool init();

};

}  // namespace menu
#endif
