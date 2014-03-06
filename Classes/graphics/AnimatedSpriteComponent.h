/*!
 * \file AnimatedSpriteComponent.h
 * \brief Abstract class for aminated sprites.
 * \author Chupee
 * \date 18/02/2014
 */
#ifndef GRAPHICS_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_ANIMATED_SPRITE_COMPONENT_H

#include "cocos2d.h"
#include "graphics/SpriteComponent.h"
#include "graphics/AnimationType.h"
#include "core/ActorState.h"
#include "core/SynthAnimation.h"

USING_NS_CC;

namespace graphics {
/**
 * launch animation for the sprite :
 * - use runAction() method
 * 	- RepeatForEver pour les loops
 * 	- Sequence for chained anims with Repeat & CallFunc
 */

/*! \class AnimatedSpriteComponent
 * \brief Abstract class for aminated sprites.
 *
 * 
 */
class AnimatedSpriteComponent : public SpriteComponent {

public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~AnimatedSpriteComponent();

	/*! \brief Callback function of chained animation */
	void requestNextAnimation();

protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	AnimatedSpriteComponent();
	AnimatedSpriteComponent(Layer* pParent);

	virtual void initListeners();

	void runAnimation(core::SynthAnimation* pAnimation, Animate* pAnimate);

	void onChangePosition(EventCustom* pEvent);

	/*
	 * Members
	 */

	/*! \brief The current state of the animated actor (eg on_air, on_floor) */
	core::ActorState _eState;

	/*! \brief The current animation */
	graphics::AnimationType _eCurrentAnimType;
};

}  // namespace graphics
#endif
