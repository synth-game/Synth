/* *****************************************************
 *      SynthComponent.cpp - @ Tom Duchêne - 30/01/14
 ***************************************************** */

#include "SynthComponent.h"

namespace core
{

SynthComponent::~SynthComponent()
{
}

bool SynthComponent::init(const char* sComponentType) {
    Component::setName(sComponentType);
    initListeners();
    return true;
}


}  // namespace core
