#ifndef MENU_SETTINGS_LAYER_H
#define MENU_SETTINGS_LAYER_H

#include "GUI/CCControlExtension/CCControlSlider.h"
#include "GUI/CCControlExtension/CCControlSaturationBrightnessPicker.h"
#include "Menu/KeysLayer.h"
#include "Menu/InGameMenuLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace menu
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

	bool init();

};

}  // namespace menu
#endif
