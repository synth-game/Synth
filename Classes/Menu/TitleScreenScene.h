#ifndef MENU_TITLE_SCREEN_SCENE_H
#define MENU_TITLE_SCREEN_SCENE_H

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlButton.h"

USING_NS_CC;

namespace menu
{
class TitleScreenScene : public Scene
{
private:
	Layer* _pButtonLayer;

	Layer* _pBackgroundLayer;

	Layer _pSettingsLayer;

	extension::ControlButton* _pBtnNewGame;

	extension::ControlButton* _pBtnPlay;

	extension::ControlButton* _pBtnSelectLevel;

	extension::ControlButton* _pBtnSettings;

	extension::ControlButton* _pBtnCredits;

	extension::ControlButton* _pBtnQuit;

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
