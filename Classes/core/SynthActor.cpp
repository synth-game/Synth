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
