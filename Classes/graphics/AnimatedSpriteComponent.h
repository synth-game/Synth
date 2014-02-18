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

	SpriteBatchNode* _pBatchNode;

	SpriteFrameCache* _pFrameCache;

	std::string _sState;

	std::string _sCurrentAnimName;



};

}  // namespace graphics
#endif
