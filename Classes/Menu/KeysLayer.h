#ifndef MENU_KEYS_LAYER_H
#define MENU_KEYS_LAYER_H

#include "cocos2d.h"
#include "InGameMenuLayer.h"

USING_NS_CC;

namespace menu
{
class KeysLayer : public Layer
{
private:
	Layer* _pButtonLayer;

	int _iSelectedButtonID;

	/**
	 *  = 6
	 *
	 *
	 */
	int _iButtonCount;


protected:
	KeysLayer();

	void onKeyPressed(Event* pEvent);

public:
	/**
	 *
	 */
	~KeysLayer();

	static InGameMenuLayer* create(int* pBackground);

	bool init();

};

}  // namespace menu
#endif
