/*!
 * \file AnimatedSpriteComponent.h
 * \brief Abstract class for aminated sprites.
 * \author Chupee
 * \date 18/02/2014
 */
#ifndef GRAPHICS_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_ANIMATED_SPRITE_COMPONENT_H

#include "cocos2d.h"
#include "Graphics/SpriteComponent.h"

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

protected:
	/*
	 * Methods
	 */

	/*! \brief Constructor */
	AnimatedSpriteComponent();
	AnimatedSpriteComponent(Layer* pParent);

	/*! \brief Callback function of chained animation */
	void requestNextAnimation();

	/*
	 * Members
	 */

	/*! \brief The batch node of the animation (takes the pvr file) */
	SpriteBatchNode* _pBatchNode;

	/*! \brief The cache of the images (takes the plist file) */
	SpriteFrameCache* _pFrameCache;

	/*! \brief The current state of the animated actor (eg on_air, on_floor) */
	std::string _sState;

	/*! \brief The current animation */
	std::string _sCurrentAnimName;



};

}  // namespace graphics
#endif
