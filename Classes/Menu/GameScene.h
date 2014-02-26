/*!
 * \file GameScene.h
 * \brief Scene in which the game is played
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef MENU_GAME_SCENE_H
#define MENU_GAME_SCENE_H

#include "cocos2d.h"
#include "Game/GameManager.h"
#include "Menu/InGameMenuLayer.h"

USING_NS_CC;

/*! \namespace menu
 *
 * namespace regrouping layers and scenes
 */
namespace menu {

/*! \class GameScene
 * \brief Scene in which the game is played
 */
class GameScene : public Scene {
public:
	/*! \brief Destructor */
	~GameScene();

	static GameScene* create();
	bool init();
	void launchLevel(int iLevelID);

protected:
	/*! \brief Constructor */
	GameScene();

	void onDeathEvent(Event* pEvent);
	void onResetLevelEvent(Event* pEvent);
	void onPauseGameEvent(Event* pEvent);
	void onResumeGameEvent(Event* pEvent);

	game::GameManager* _pGameLayer;
	InGameMenuLayer* _pMenu;

	EventListenerCustom* _pDeathEventListener;
	EventListenerCustom* _pResetLevelEventListener;
	EventListenerCustom* _pPauseGameEventListener;
	EventListenerCustom* _pResumeGameEventListener;
};

}  // namespace menu
#endif
