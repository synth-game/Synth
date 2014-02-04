/* *****************************************************
 *		SynthManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef CORE_SYNTH_MANAGER_H
#define CORE_SYNTH_MANAGER_H

#include "cocos2d.h"
#include "Game/GameScene.h"
#include "Menu/TitleScreenScene.h"
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

	EventListenerCustom* _pNewGameEventListener;

	EventListenerCustom* _pContinueGameEventListener;

	EventListenerCustom* _pOpenSelectLevelScreenEventListener;

	EventListenerCustom* _pOpenSettingsEventListener;

	EventListenerCustom* _pOpenCreditsEventListener;

	EventListenerCustom* _pExitGameEventListener;

	EventListenerCustom* _pOpenTitleScreenEventListener;

	EventListenerCustom* _pLoadSelectedLevelEventListener;


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

	bool init();

};

}  // namespace Core
#endif
