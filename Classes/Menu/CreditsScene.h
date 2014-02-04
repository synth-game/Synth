#ifndef MENU_CREDITS_SCENE_H
#define MENU_CREDITS_SCENE_H

#include "Menu/Scene.h"
#include "Menu/ControlButton.h"
#include "Menu/EventListenerKeyBoard.h"
#include "Menu/Event.h"
#include "Graphics/Layer.h"

namespace Menu
{
class CreditsScene : public Scene
{
private:
	Graphics::Layer* _pMainLayer;

	Graphics::Layer* _pBackgroundLayer;

	ControlButton* _pBtnBack;

	EventListenerKeyBoard _keyEventListener;


protected:
	/**
	 *  
	 */
	CreditsScene();

	void onKeyPress(Event* pEvent);

public:
	~CreditsScene();

	static CreditsScene* create(int* pBackground);

	void init();

};

}  // namespace Menu
#endif