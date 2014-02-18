/*!
 * \file AnimatedSpriteComponent.cpp
 * \brief Abstract class for aminated sprites.
 * \author Chupee
 * \date 18/02/2014
 */
#include "AnimatedSpriteComponent.h"

namespace graphics {

AnimatedSpriteComponent::AnimatedSpriteComponent() {

}

AnimatedSpriteComponent::AnimatedSpriteComponent(Layer* pParent) :
	SpriteComponent(pParent),
	_pFrameCache(nullptr),
	_pBatchNode(nullptr),
	_sState(NULL),
	_sCurrentAnimName(NULL) {
}

AnimatedSpriteComponent::~AnimatedSpriteComponent() {
}

void AnimatedSpriteComponent::requestNextAnimation() {
}

}  // namespace graphics
