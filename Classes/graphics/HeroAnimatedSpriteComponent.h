/*!
 * \file HeroAnimatedSpriteComponent.h
 * \brief Gives an animated sprite to a hero.
 * \author Chupee
 * \date 18/02/2014
 */
#ifndef GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H

#include "cocos2d.h"
#include "Graphics/AnimatedSpriteComponent.h"

USING_NS_CC;

namespace graphics {
/*! \class HeroAnimatedSpriteComponent
 * \brief Gives an animated sprite to a hero.
 *
 * 
 */
class HeroAnimatedSpriteComponent : public AnimatedSpriteComponent {
public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~HeroAnimatedSpriteComponent();

	virtual bool init();

	/*! \brief Get the batchnode from the GraphicManager and init with the idl_animation */
	static HeroAnimatedSpriteComponent* create();

	void onChangePosition(EventCustom* pEvent);

	void onEditMove(EventCustom* pEvent);

	void onJump(EventCustom* pEvent);

	void onInterruptMove(EventCustom* pEvent);

	void onChangeNodeOwner(EventCustom* pEvent);

	void onToggleLight(EventCustom* pEvent);

	void onDeath(EventCustom* pEvent);

	void onWin(EventCustom* pEvent);

	void onResetLevel(EventCustom* pEvent);

	/*
	 * Members
	 */
	static const char* COMPONENT_TYPE;


protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	HeroAnimatedSpriteComponent();

	void initListeners();


private:
	/*
	 * Methods
	 */

	EventListenerCustom* pChangePositionEventListener;

	EventListenerCustom* pEditMoveEventListener;

	EventListenerCustom* pJumpEventListener;

	EventListenerCustom* pInterruptMoveEventListener;

	EventListenerCustom* pChangeNodeOwnerEventListener;

	EventListenerCustom* pToggleLightEventListener;

	EventListenerCustom* pDeathEventListener;

	EventListenerCustom* pWinEventListener;

	EventListenerCustom* pResetLevelEventListener;

};

}  // namespace graphics
#endif
