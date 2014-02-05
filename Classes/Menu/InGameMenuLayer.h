#ifndef MENU_IN_GAME_MENU_LAYER_H
#define MENU_IN_GAME_MENU_LAYER_H

#include "Menu/ControlButton.h"
#include "Menu/Event.h"
#include "Graphics/Layer.h"

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
