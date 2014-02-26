/*!
 * \file SynthAnimation.cpp
 * \brief Base classe of Synth game objects
 * \author Chupee
 * \date 25/02/2014
 */
#include "SynthAnimation.h"

namespace core {

SynthAnimation::SynthAnimation(graphics::AnimationType eTag, graphics::AnimationType eNextTag, Animation* pAnimation, bool bIsLoop) :
	_eTag(eTag),
	_eNextTag(eNextTag), 
	_pAnimation(pAnimation),
	_bIsLoop(bIsLoop) {
}

SynthAnimation::SynthAnimation(graphics::AnimationType eTag, Animation* pAnimation, bool bIsLoop) :
	_eTag(eTag),
	_eNextTag(), 
	_pAnimation(pAnimation),
	_bIsLoop(bIsLoop) {
}

SynthAnimation::~SynthAnimation() {

}

}  // namespace core
