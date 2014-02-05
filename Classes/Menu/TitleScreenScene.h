#ifndef MENU_TITLE_SCREEN_SCENE_H
#define MENU_TITLE_SCREEN_SCENE_H

#include "cocos2d.h"
#include "Menu/ControlButton.h"

USING_NS_CC;

namespace menu
{
class TitleScreenScene : public Scene
{
private:
	Layer* _pButtonLayer;

	Layer* _pBackgroundLayer;

	Layer _pSettingsLayer;

	ControlButton* _pBtnNewGame;

	ControlButton* _pBtnPlay;

	ControlButton* _pBtnSelectLevel;

	ControlButton* _pBtnSettings;

	ControlButton* _pBtnCredits;

	ControlButton* _pBtnQuit;

	int _iSelectedButtonID;

	/**
	 *  = 6
	 *
	 *
	 */
	int _iButtonCount;


protected:
	TitleScreenScene();

	void onKeyPress(Event* pEvent);

public:
	~TitleScreenScene();

	static TitleScreenScene* create(int* pBackground, bool bIsThereGame);

	bool init();

};

}  // namespace menu
#endif
