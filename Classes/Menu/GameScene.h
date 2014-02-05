#ifndef MENU_GAME_SCENE_H
#define MENU_GAME_SCENE_H


#include "Menu/Scene.h"
#include "Menu/GameManager.h"
#include "Menu/InGameMenuLayer.h"
#include "Menu/Event.h"

namespace menu
{
class GameScene : public Scene
{
private:
	GameManager* _pGameLayer;

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
