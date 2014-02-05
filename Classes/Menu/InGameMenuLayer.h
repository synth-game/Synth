#ifndef MENU_IN_GAME_MENU_LAYER_H
#define MENU_IN_GAME_MENU_LAYER_H

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlButton.h"

USING_NS_CC;

namespace menu
{
class InGameMenuLayer : public Layer
{
private:
	Layer* _pBackgroundLayer;

	Layer* _pButtonLayer;

	Layer* _pSettingsLayer;

	extension::ControlButton* _pBtnResumeGame;

	extension::ControlButton* _pBtnMainMenu;

	extension::ControlButton* _pBtnRetry;

	extension::ControlButton* _pBtnSelectLevel;

	extension::ControlButton* _pBtnSettings;

	extension::ControlButton* _pBtnQuit;

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
