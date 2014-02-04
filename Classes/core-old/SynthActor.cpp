#include "SynthActor.h"

int SynthActor::_iActorCount = 0;

SynthActor::SynthActor(string sTag)
	: Node(), _iActorID(_iActorCount++), _sTag(sTag){

}

SynthActor::~SynthActor() {

}