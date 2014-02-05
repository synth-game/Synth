#ifndef GRAPHICS_ANIMATED_SPRITE_COMPONENT_H
#define GRAPHICS_ANIMATED_SPRITE_COMPONENT_H

#include "Graphics/SpriteComponent.h"
#include "Graphics/SpriteBatchNode.h"

namespace graphics
{
/**
 * launch animation for the sprite :
 * - use runAction() method
 * 	- RepeatForEver pour les loops
 * 	- Sequence for chained anims with Repeat & CallFunc
 */
class AnimatedSpriteComponent : public SpriteComponent
{
protected:
	SpriteBatchNode* _pBatchNode;

	string _sState;

	string _sCurrentAnimName;


protected:
	/**
	 *
	 */
	AnimatedSpriteComponent();

	/**
	 * callback function of chained animation
	 */
	void requestNextAnimation();

public:
	/**
	 *
	 */
	~AnimatedSpriteComponent();

};

}  // namespace graphics
#endif
