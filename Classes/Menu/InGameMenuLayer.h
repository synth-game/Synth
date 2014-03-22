/*!
 * \file InGameMenuLayer.h
 * \brief The menu during the game
 * \author Chupee
 * \date 20/03/2014
 */
#ifndef MENU_IN_GAME_MENU_LAYER_H
#define MENU_IN_GAME_MENU_LAYER_H

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace menu {

class InGameMenuLayer : public Layer {

public:

	~InGameMenuLayer();

	static InGameMenuLayer* create();

	bool init();

protected:
	InGameMenuLayer();

	void onKeyPressed(Event* pEvent);

	void dispatchExitGameEvent(Object* pSender);
	void dispatchResumeGameEvent(Object* pSender);
	void dispatchReselLevelEvent(Object* pSender);

private:
	Layer* _pBackgroundLayer;

	Menu* _pMenuLayer;

	Layer* _pSettingsLayer;

	MenuItem* _pBtnResumeGame;

	ControlButton* _pBtnMainMenu;

	MenuItem* _pBtnRetry;

	ControlButton* _pBtnSelectLevel;

	ControlButton* _pBtnSettings;

	MenuItem* _pBtnQuit;

	int _iSelectedButtonID;

	int _iButtonCount;

	


};

}  // namespace menu
#endif
