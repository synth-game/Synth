/*!
 * \file FireflyAnimatedSpriteComponent.h
 * \brief Add a sprite image (fixed) to the actor.
 * \author Chupee
 * \date 18/02/2014
 */
#ifndef GRAPHICS_FIRE_FLY_ANIMATED_SPRITE_H
#define GRAPHICS_FIRE_FLY_ANIMATED_SPRITE_H

#include "cocos2d.h"
#include "Graphics/AnimatedSpriteComponent.h"

USING_NS_CC;

namespace graphics {

class FireFlyAnimatedSpriteComponent : public AnimatedSpriteComponent {
	
public:
	~FireFlyAnimatedSpriteComponent();

	static FireFlyAnimatedSpriteComponent* create();

	void onChangeNodeOwner(EventCustom* pEvent);


protected:
	FireFlyAnimatedSpriteComponent();

	void initListeners();

private:
	EventListenerCustom* pChangeNodeOwnerEventListener;

};

}  // namespace graphics
#endif
