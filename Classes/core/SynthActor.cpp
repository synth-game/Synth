#include "SynthActor.h"

namespace core
{
int SynthActor::_iActorCount;

SynthActor::SynthActor(std::string sTag) {
}

int SynthActor::getActorID()
{
	return 0;
}

std::string SynthActor::getTag()
{
	return "";
}
}  // namespace core
