/*!
 * \file FireflyAnimatedSpriteComponent.cpp
 * \brief Add a sprite image (fixed) to the actor.
 * \author Chupee
 * \date 18/02/2014
 */
#include "FireFlyAnimatedSpriteComponent.h"

namespace graphics {

FireFlyAnimatedSpriteComponent::FireFlyAnimatedSpriteComponent() :
	AnimatedSpriteComponent() {
}

FireFlyAnimatedSpriteComponent::~FireFlyAnimatedSpriteComponent() {
}

FireFlyAnimatedSpriteComponent* FireFlyAnimatedSpriteComponent::create() {
	return 0;
}

void FireFlyAnimatedSpriteComponent::initListeners() {
}

void FireFlyAnimatedSpriteComponent::onChangeNodeOwner(EventCustom* pEvent) {
}

}  // namespace graphics
