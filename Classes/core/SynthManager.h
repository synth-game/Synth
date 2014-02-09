#ifndef CORE_SYNTH_MANAGER_H
#define CORE_SYNTH_MANAGER_H

#include "cocos2d.h"
#include "menu/GameScene.h"
#include "menu/TitleScreenScene.h"
#include "menu/SelectLevelScene.h"
#include "menu/CreditsScene.h"

namespace core
{
class SynthManager
{
private:
	menu::TitleScreenScene* _pTitleScreenScene;

	menu::CreditsScene* _pCreditsScene;

	menu::GameScene* _pGameScene;

	menu::SelectLevelScene* _pSelectLevelScene;

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

	void init();

};

}  // namespace core
#endif
