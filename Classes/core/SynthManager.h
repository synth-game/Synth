/*!
 * \file SynthManager.h
 * \brief Main manager, the entry point of our program
 * \author Jijidici
 * \date 09/02/2014
 */
#ifndef CORE_SYNTH_MANAGER_H
#define CORE_SYNTH_MANAGER_H

#include "cocos2d.h"
#include "menu/GameScene.h"
#include "menu/TitleScreenScene.h"
#include "menu/SelectLevelScene.h"
#include "menu/CreditsScene.h"

namespace core {

/*! \class SynthManager
 * \brief Main manager, the entry point of our program
 */
class SynthManager {
public:
	/*! \brief Constructor */
	SynthManager();
	/*! \brief Destructor */
	~SynthManager();

	void init();

private:
	void onNewGameEvent(EventCustom* event);
	void onContinueGameEvent(EventCustom* event);
	void onOpenTitleScreenEvent(EventCustom* event);
	void onOpenCreditsEvent(EventCustom* event);
	void onOpenSelectLevelScreenEvent(EventCustom* event);
	void onLoadSelectedLevelEvent(EventCustom* event);
	void onExitGameEvent(EventCustom* event);

	void displayLoading();
	void removeLoading();

	menu::TitleScreenScene* _pTitleScreenScene;
	menu::CreditsScene* _pCreditsScene;
	menu::GameScene* _pGameScene;
	menu::SelectLevelScene* _pSelectLevelScene;

	EventListenerCustom* _pNewGameEventListener;
	EventListenerCustom* _pContinueGameEventListener;
	EventListenerCustom* _pOpenTitleScreenEventListener;
	EventListenerCustom* _pOpenCreditsEventListener;
	EventListenerCustom* _pOpenSelectLevelScreenEventListener;
	EventListenerCustom* _pLoadSelectedLevelEventListener;
	EventListenerCustom* _pExitGameEventListener;
};

}  // namespace core
#endif
