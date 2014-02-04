#ifndef MENU_SETTINGS_LAYER_H
#define MENU_SETTINGS_LAYER_H

#include "Menu/KeysLayer.h"
#include "Menu/ControlSlider.h"
#include "Menu/ControlSaturationBrightnessPicker.h"
#include "Menu/Event.h"
#include "Menu/InGameMenuLayer.h"
#include "Graphics/Layer.h"

namespace Menu
{
class SettingsLayer : public Layer
{
private:
	Layer* _pButtonLayer;

	KeysLayer* _pKeysLayer;

	ControlSlider* _pSliderMusicVolume;

	ControlSlider* _pSliderSoundsVolume;

	ControlSaturationBrightnessPicker* _pPickerLuminosity;

	int _iSelectedButtonID;

	/**
	 *  = 6
	 *
	 *
	 */
	int _iButtonCount;


protected:
	SettingsLayer();

	void onKeyPressed(Event* pEvent);

public:
	/**
	 *
	 */
	~SettingsLayer();

	static InGameMenuLayer* create(int* pBackground);

	void init();

};

}  // namespace Menu
#endif
