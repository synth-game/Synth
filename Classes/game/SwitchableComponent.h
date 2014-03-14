/*!
 * \file SwitchableComponent.h
 * \brief The actor can be turned on and off
 * \author Chupee
 * \date 14/03/2014
 */
#ifndef GAME_SWITCHABLE_COMPONENT_H
#define GAME_SWITCHABLE_COMPONENT_H

#include "cocos2d.h"
#include "Core/SynthComponent.h"

USING_NS_CC;

namespace game {

/*! \class SwitchableComponent
 * \brief The actor can be turned on and off
 *
 */
class SwitchableComponent : public core::SynthComponent {

public:
	/*
	 * Methods
	 */
	/*! \brief Desctructor */
	~SwitchableComponent();

	/*! \brief Init the component */
	bool init();

	/*! \brief Create the component */
	static SwitchableComponent* create(bool bOn);

	/*! \brief  */
	inline bool isOn() { return _bOn; };

	/*! \brief Set the owned node */
	inline void setOwnedNode(bool bOn) { _bOn = bOn; };

	/*
	 * Members
	 */

	/*! \brief The component type */
	static const char* COMPONENT_TYPE;

protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	SwitchableComponent();

	/*! \brief  */
	void initListeners();

	/*! \brief  */
	void onToggleLight(EventCustom* pEvent);

	/*! \brief  */
	void onChangeNodeOwner(EventCustom* pEvent);

	/*
	 * Members
	 */

	/*! \brief Is the actor on or off */
	bool _bOn;


private:
	/*
	 * Members
	 */

	/*! \brief  */
	EventListenerCustom* _pToggleLightEventListener;

	/*! \brief  */
	EventListenerCustom* _pChangeNodeOwnerEventListener;
};

}  // namespace game
#endif
