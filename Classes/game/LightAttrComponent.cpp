/*!
 * \file LightAttrComponent.h
 * \brief Component giving a colored light to a SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "LightAttrComponent.h"

namespace game {

char* LightAttrComponent::COMPONENT_TYPE;

LightAttrComponent::LightAttrComponent() {
}

LightAttrComponent::~LightAttrComponent() {
}

bool LightAttrComponent::init() {
	return 0;
}

LightAttrComponent* LightAttrComponent::create(Color4B color) {
	return 0;
}

Color4B LightAttrComponent::getColor() {
	return Color4B::BLACK;
}

void LightAttrComponent::setColor(Color4B color) {
}

bool LightAttrComponent::isOn() {
	return 0;
}

void LightAttrComponent::initListeners() {
}

void LightAttrComponent::onChangeIntensity(EventCustom* pEvent) {
}

float LightAttrComponent::getIntensity() {
	return 0;
}

void LightAttrComponent::setIntensity(float intensity) {
}

}  // namespace game
