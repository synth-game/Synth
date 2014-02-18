/*!
 * \file HeroAnimatedSpriteComponent.cpp
 * \brief Gives an animated sprite to a hero.
 * \author Chupee
 * \date 18/02/2014
 */
#include "HeroAnimatedSpriteComponent.h"

namespace graphics {

const char* SpriteComponent::COMPONENT_TYPE = "HeroAnimatedSpriteComponent";

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent() {
}

HeroAnimatedSpriteComponent::~HeroAnimatedSpriteComponent() {
}

bool HeroAnimatedSpriteComponent::init() {
    SynthComponent::init(HeroAnimatedSpriteComponent::COMPONENT_TYPE);
	initListeners();
	return true;
}

HeroAnimatedSpriteComponent* HeroAnimatedSpriteComponent::create() {
	return 0;
}

void HeroAnimatedSpriteComponent::initListeners() {
	//_pChangePositionEventListener = cocos2d::EventListenerCustom::create(events::ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(SpriteComponent::onEditMove, this));
	// etc.. TODO
}

void HeroAnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onEditMove(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onJump(EventCustom* pEvent) {

}

void HeroAnimatedSpriteComponent::onInterruptMove(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onChangeNodeOwner(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onToggleLight(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onDeath(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onWin(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onResetLevel(EventCustom* pEvent) {
}

}  // namespace graphics
