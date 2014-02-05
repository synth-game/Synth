#ifndef GAME_LIGHT_ATTR_COMPONENT_H
#define GAME_LIGHT_ATTR_COMPONENT_H

#include "cocos2d.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

namespace game
{
class LightAttrComponent :  core::SynthComponent
{
private:
	EventListenerCustom* _pChangeIntensityListener;


protected:
	/**
	 * Color4B : r g b a
	 * constantes: RED BLUE MAGENTA ETC...
	 */
	Color4B* _pColor;

	/**
	 * intensity of the light : between 0 and 1
	 *
	 */
	float _intensity;


public:
	static char* COMPONENT_TYPE;


protected:
	/**
	 *
	 */
	LightAttrComponent();

	void initListeners();

	void onChangeIntensity(EventCustom* pEvent);

public:
	/**
	 *
	 */
	~LightAttrComponent();

	bool init();

	static LightAttrComponent* create(Color4B color);

	Color4B getColor();

	/**
	 *
	 */
	void setColor(Color4B color);

	bool isOn();

	float getIntensity();

	/**
	 *
	 */
	void setIntensity(float intensity);

};

}  // namespace game
#endif
