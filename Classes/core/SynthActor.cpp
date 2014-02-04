/* *****************************************************
 *      SynthActor.cpp - @ Xochitl Florimont - 30/01/14
 ***************************************************** */

#include "SynthActor.h"

namespace Core
{
int SynthActor::_iActorCount;

SynthActor::SynthActor(string sTag)
    : Node(), _iActorID(_iActorCount), _sTag(sTag){
}

int SynthActor::getActorID()
{
	return _iActorID;
}

string SynthActor::getTag()
{
	return _sTag;
}
}  // namespace Core
