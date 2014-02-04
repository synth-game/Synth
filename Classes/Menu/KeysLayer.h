#ifndef MENU_KEYS_LAYER_H
#define MENU_KEYS_LAYER_H

#include "Menu/Event.h"
#include "Menu/InGameMenuLayer.h"
#include "Graphics/Layer.h"

namespace Menu
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

	void init();

};

}  // namespace Menu
#endif
