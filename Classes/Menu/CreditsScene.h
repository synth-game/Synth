#ifndef MENU_CREDITS_SCENE_H
#define MENU_CREDITS_SCENE_H

#include "cocos2d.h"
#include "GUI/CCControlExtension/CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace menu
{
class CreditsScene : public Scene
{
private:
	Layer* _pMainLayer;

	Layer* _pBackgroundLayer;

	ControlButton* _pBtnBack;

	EventListenerKeyboard* _pKeyEventListener;


protected:
	/**
	 *
	 */
	CreditsScene();

	void onKeyPress(Event* pEvent);

public:
	~CreditsScene();

	static CreditsScene* create(int* pBackground);

	bool init();

};

}  // namespace menu
#endif
