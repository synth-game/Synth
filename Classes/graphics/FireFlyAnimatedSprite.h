#ifndef GRAPHICS_FIRE_FLY_ANIMATED_SPRITE_H
#define GRAPHICS_FIRE_FLY_ANIMATED_SPRITE_H

#include "cocos2d.h"
#include "Graphics/AnimatedSpriteComponent.h"

USING_NS_CC;

namespace graphics
{
class FireFlyAnimatedSprite : public AnimatedSpriteComponent
{
private:
	EventListenerCustom* pChangeNodeOwnerEventListener;


protected:
	FireFlyAnimatedSprite();

	/**
	 *
	 */
	void initListeners();

public:
	~FireFlyAnimatedSprite();

	static FireFlyAnimatedSprite* create();

	void onChangeNodeOwner(EventCustom* pEvent);

};

}  // namespace graphics
#endif
