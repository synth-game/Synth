#ifndef GAME_LIGHT_ATTR_COMPONENT_H
#define GAME_LIGHT_ATTR_COMPONENT_H

#include "Component.h"
#include "Color4B.h"
#include "EventCustom.h"
#include "Physics/EventListenerCustom.h"
#include "Game/SynthComponent.h"
#include "Core/SynthComponent.h"

namespace Game
{
class LightAttrComponent : public Component, public SynthComponent, public Core::SynthComponent
{
private:
	Physics::EventListenerCustom* _pChangeIntensityListener;


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

	boolean init();

	static LightAttrComponent* create(Color4B color);

	Color4B getColor();

	/**
	 *  
	 */
	void setColor(Color4B color);

	boolean isOn();

	float getIntensity();

	/**
	 *  
	 */
	void setIntensity(float intensity);

};

}  // namespace Game
#endif
