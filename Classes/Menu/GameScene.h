#ifndef MENU_GAME_SCENE_H
#define MENU_GAME_SCENE_H

#include "cocos2d.h"
#include "Game/GameManager.h"
#include "Menu/InGameMenuLayer.h"

USING_NS_CC;

namespace menu
{
class GameScene : public Scene
{
private:
	game::GameManager* _pGameLayer;

	InGameMenuLayer* _pMenu;

	EventListenerCustom* _pDeathEventListener;

	EventListenerCustom* _pResetLevelEventListener;

	EventListenerCustom* _pPauseGameEventListener;

	EventListenerCustom* _pResumeGameEventListener;


protected:
	GameScene();

	void onDeathEvent(Event* pEvent);

	void onResetLevelEvent(Event* pEvent);

	void onPauseGameEvent(Event* pEvent);

	void onResumeGameEvent(Event* pEvent);

public:
	~GameScene();

	static GameScene* create();

	bool init();

	void launchLevel(int iLevelID);

};

}  // namespace menu
#endif
