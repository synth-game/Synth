#ifndef MENU_TITLE_SCREEN_SCENE_H
#define MENU_TITLE_SCREEN_SCENE_H

#include "Menu/Scene.h"
#include "Menu/ControlButton.h"
#include "Menu/Event.h"
#include "Graphics/Layer.h"

namespace Menu
{
class TitleScreenScene : public Scene
{
private:
	Graphics::Layer* _pButtonLayer;

	Graphics::Layer* _pBackgroundLayer;

	Graphics::Layer _pSettingsLayer;

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

	void init();

};

}  // namespace Menu
#endif
