/* *****************************************************
 *		SynthManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef CORE_SYNTH_MANAGER_H
#define CORE_SYNTH_MANAGER_H

#include "cocos2d.h"
#include "game/GameManager.h"
#include "Game/GameScene.h"
#include "Core/TitleScreenScene.h"
#include "Menu/SelectLevelScene.h"

namespace Core
{
class SynthManager
{
private:
	TitleScreenScene* _pTitleScreenScene;

	CreditsScene_ _pCreditsScene;

	Game::GameScene* _pGameScene;

	Menus::SelectLevelScene* _pSelectLevelScene;

	Physics::EventListenerCustom* _pNewGameEventListener;

	Physics::EventListenerCustom* _pContinueGameEventListener;

	Physics::EventListenerCustom* _pOpenSelectLevelScreenEventListener;

	Physics::EventListenerCustom* _pOpenSettingsEventListener;

	Physics::EventListenerCustom* _pOpenCreditsEventListener;

	Physics::EventListenerCustom* _pExitGameEventListener;

	Physics::EventListenerCustom* _pOpenTitleScreenEventListener;

	Physics::EventListenerCustom* _pLoadSelectedLevelEventListener;


protected:
	void onNewGameEvent(EventCustom* event);

	void onContinueGameEvent(EventCustom* event);

	void onOpenSelectLevelScreenEvent(EventCustom* event);

	void onOpenSettingsEvent(EventCustom* event);

	void onOpenCreditsEvent(EventCustom* event);

	void onExitGameEvent(EventCustom* event);

	void onOpenTitleScreenEvent(EventCustom* event);

	void onLoadSelectedLevelEvent(EventCustom* event);

public:
	SynthManager();

	~SynthManager();

	void init();

};

}  // namespace Core
#endif
