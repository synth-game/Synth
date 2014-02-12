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

/*! \class LightAttrComponent
 * \brief Component giving a colored light to a SynthActor.
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

	/*! \brief Initialize the component thanks to its COMPONENT_TYPE
	 * \return true
	 */
	bool init();

	/*! \brief Create the component
	 * \param color The color of the light (r,g,b,a)
	 * \return LightAttrComponent*
	 */
	static LightAttrComponent* create(Color4B* pColor);

	inline Color4B getColor();

	inline void setColor(Color4B color);

	inline bool isOn();

	inline float getIntensity();

	inline void setIntensity(float intensity);

	/*
	 * Members
	 */

	/*! \brief The identifier of the component. */
	static const char* COMPONENT_TYPE;


protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	LightAttrComponent();

	/*! \brief Initialize the listeners
	 * \return void
	 */
	void initListeners();

	/*! \brief Method called when a ChangeIntensityEvent is catched
	 * \param pEvent the event catched
	 * \return void
	 */
	void onChangeIntensity(EventCustom* pEvent);

	/*
	 * Members
	 */

	/*! \brief The color of the light (r,g,b,a) */
	Color4B* _pColor;

	/*! \brief The intensity of the light. The alpha layer from _pColor member */
	float _intensity;


private:
	/*
	 * Members
	 */

	/*! \brief ChangePositionEvent listener. */
	EventListenerCustom* _pChangeIntensityListener;


};

}  // namespace game
#endif
