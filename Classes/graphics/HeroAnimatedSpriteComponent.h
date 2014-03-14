/*!
 * \file HeroAnimatedSpriteComponent.h
 * \brief Gives an animated sprite to a hero.
 * \author Chupee
 * \date 18/02/2014
 */
#ifndef GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_HERO_ANIMATED_SPRITE_COMPONENT_H

#include "cocos2d.h"
#include "core/SynthAnimation.h"
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
	static HeroAnimatedSpriteComponent* create(Layer* pParent);

	void onEnter();

	void onEditMove(EventCustom* pEvent);

	void onJump(EventCustom* pEvent);

	void onInterruptMove(EventCustom* pEvent);

	void onChangeNodeOwner(EventCustom* pEvent);

	void onToggleLight(EventCustom* pEvent);

	void onDeath(EventCustom* pEvent);

	void onWin(EventCustom* pEvent);

	void onResetLevel(EventCustom* pEvent);

	void onChangeState(EventCustom* pEvent);

	/*
	 * Members
	 */


protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	HeroAnimatedSpriteComponent(Layer* pParent);

	void initListeners();

private:
	/*
	 * Methods
	 */

	

	/*
	 * Members
	 */

	EventListenerCustom* _pChangePositionEventListener;

	EventListenerCustom* _pEditMoveEventListener;

	EventListenerCustom* _pJumpEventListener;

	EventListenerCustom* _pInterruptMoveEventListener;

	EventListenerCustom* _pChangeNodeOwnerEventListener;

	EventListenerCustom* _pToggleLightEventListener;

	EventListenerCustom* _pDeathEventListener;

	EventListenerCustom* _pWinEventListener;

	EventListenerCustom* _pResetLevelEventListener;

	EventListenerCustom* _pChangeStateEventListener;

};

}  // namespace graphics
#endif
