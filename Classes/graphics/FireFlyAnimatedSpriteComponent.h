/*!
 * \file FireflyAnimatedSpriteComponent.h
 * \brief Add animated sprite to a firefly
 * \author Chupee
 * \date 18/02/2014
 */
#ifndef GRAPHICS_FIRE_FLY_ANIMATED_SPRITE_H
#define GRAPHICS_FIRE_FLY_ANIMATED_SPRITE_H

#include "cocos2d.h"
#include "Graphics/AnimatedSpriteComponent.h"

USING_NS_CC;

namespace graphics {

/*! \class FireflyAnimatedSpriteComponent
 * \brief Add animated sprite to a firefly
 *
 * 
 */
class FireFlyAnimatedSpriteComponent : public AnimatedSpriteComponent {
	
public:
	/*! \brief Destructor */
	~FireFlyAnimatedSpriteComponent();

	virtual bool init();

	static FireFlyAnimatedSpriteComponent* create(Layer* pParent);

	void onEnter();

	void onChangeNodeOwner(EventCustom* pEvent);


protected:
	/*! \brief Constructor */
	FireFlyAnimatedSpriteComponent(Layer* pParent);

	void initListeners();

private:
	EventListenerCustom* _pChangeNodeOwnerEventListener;

};

}  // namespace graphics
#endif
