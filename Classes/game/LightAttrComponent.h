/*!
 * \file LightAttrComponent.h
 * \brief Component giving a colored light to a SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#ifndef GAME_LIGHT_ATTR_COMPONENT_H
#define GAME_LIGHT_ATTR_COMPONENT_H

#include "cocos2d.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

namespace game {

/*! \class GeometryComponent
 * \brief Class giving a position, a size, a rotation angle and an anchorpoint to the SynthActor.
 *
 * 
 */
class LightAttrComponent :  core::SynthComponent {

public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~LightAttrComponent();

	bool init();

	static LightAttrComponent* create(Color4B color);

	Color4B getColor();

	void setColor(Color4B color);

	bool isOn();

	float getIntensity();

	void setIntensity(float intensity);

	/*
	 * Members
	 */

	static char* COMPONENT_TYPE;


protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	LightAttrComponent();

	void initListeners();

	void onChangeIntensity(EventCustom* pEvent);

	/*
	 * Members
	 */

	Color4B* _pColor;

	float _intensity;


private:
	/*
	 * Members
	 */

	EventListenerCustom* _pChangeIntensityListener;


};

}  // namespace game
#endif
