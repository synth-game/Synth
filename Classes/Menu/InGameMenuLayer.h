#ifndef MENU_IN_GAME_MENU_LAYER_H
#define MENU_IN_GAME_MENU_LAYER_H

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace menu
{
class InGameMenuLayer : public Layer
{
private:
	Layer* _pBackgroundLayer;

	Layer* _pButtonLayer;

	Layer* _pSettingsLayer;

	ControlButton* _pBtnResumeGame;

	ControlButton* _pBtnMainMenu;

	ControlButton* _pBtnRetry;

	ControlButton* _pBtnSelectLevel;

	ControlButton* _pBtnSettings;

	ControlButton* _pBtnQuit;

	int _iSelectedButtonID;

	/**
	 *  = 6
	 *
	 *
	 */
	int _iButtonCount;


protected:
	InGameMenuLayer();

	void onKeyPressed(Event* pEvent);

public:
	/**
	 *
	 */
	~InGameMenuLayer();

	static InGameMenuLayer* create(int* pBackground);

	bool init();

};

}  // namespace menu
#endif
