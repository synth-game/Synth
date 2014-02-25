/*!
 * \file SynthAnimation.h
 * \brief A synth animation
 * \author Chupee
 * \date 25/02/2014
 */
#ifndef CORE_SYNTH_ANIMATION_H
#define CORE_SYNTH_ANIMATION_H

#include <string>
#include "cocos2d.h"
#include "core/ActorType.h"
#include "graphics/AnimationType.h"

USING_NS_CC;

/*! \namespace core
 *
 * namespace of all essential and mother classes
 */
namespace core {

/*! \class SynthAnimation
 * \brief A synth animation
 *
 * 
 */
class SynthAnimation {
public:
	/*! \brief Constructor
	 * 
	 * Constructor which initializes the SynthActor tag
	 * \param eType : type of the actor
	 */
	SynthAnimation();

	/*! \brief Destructor */
	~SynthAnimation();

	inline graphics::AnimationType getTag() { return _eTag; }
	inline bool bIsLoop() { return _bIsLoop; }
	inline graphics::AnimationType getNextTag() { return _eNextTag; }

	inline void setTag( graphics::AnimationType eTag ) { _eTag = eTag; }
	inline void setIsLoop( bool bIsLoop) { _bIsLoop = bIsLoop; }
	inline void setTag( graphics::AnimationType eNextTag ) { _eNextTag = eNextTag; }



protected:

	graphics::AnimationType _eTag;

	bool _bIsLoop;

	graphics::AnimationType _eNextTag;

};

}  // namespace core
#endif
