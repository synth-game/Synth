/*!
 * \file TitleScreenScene.h
 * \brief The title screen of the game
 * \author Chupee
 * \date 17/03/2014
 */
#ifndef MENU_TITLE_SCREEN_SCENE_H
#define MENU_TITLE_SCREEN_SCENE_H

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace menu {

/*!
 * \class TitleScreenScene
 * \brief The title screen of the game
 *
 */
class TitleScreenScene : public Scene {

public:
	~TitleScreenScene();

	static TitleScreenScene* create(int* pBackground, bool bIsThereGame);

	bool init();

protected:
	TitleScreenScene();

	void onKeyPress(Event* pEvent);

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

	int _iButtonCount;





};

}  // namespace menu
#endif
