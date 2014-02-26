/*!
 * \file SynthComponent.cpp
 * \brief Base classe of components in the game
 * \author Jijidici
 * \date 09/02/2014
 */
#include "SynthComponent.h"

namespace core {

SynthComponent::SynthComponent() 
	: Component() {

}

SynthComponent::~SynthComponent() {

}

bool SynthComponent::init(const char* sComponentType) {
	Component::setName(sComponentType);
	initListeners();
    return true;
}


}  // namespace core
