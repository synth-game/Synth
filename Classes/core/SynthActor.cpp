/* *****************************************************
 *      SynthActor.cpp - @ Xochitl Florimont - 30/01/14
 ***************************************************** */

#include "SynthActor.h"

namespace core
{
int SynthActor::_iActorCount;

SynthActor::SynthActor(std::string sTag)
    : Node(), _iActorID(_iActorCount), _sTag(sTag){
}

int SynthActor::getActorID()
{
	return _iActorID;
}

std::string SynthActor::getTag()
{
	return _sTag;
}
}  // namespace core
