/*!
 * \file SynthActor.cpp
 * \brief Base classe of Synth game objects
 * \author Jijidici
 * \date 09/02/2014
 */
#include "SynthActor.h"

namespace core {

int SynthActor::_iActorCount = 0;

SynthActor::SynthActor(std::string sTag) 
	: Node()
	, _sTag(sTag) 
	, _iActorID(++_iActorCount) {
}

SynthActor::~SynthActor() {

}

}  // namespace core
