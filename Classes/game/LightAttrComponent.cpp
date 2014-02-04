#include "LightAttrComponent.h"

namespace Game
{
char* LightAttrComponent::COMPONENT_TYPE;

LightAttrComponent::LightAttrComponent()
{
}

LightAttrComponent::~LightAttrComponent()
{
}

bool LightAttrComponent::init()
{
	return 0;
}

LightAttrComponent* LightAttrComponent::create(Color4B color)
{
	return 0;
}

Color4B LightAttrComponent::getColor()
{
	return 0;
}

void LightAttrComponent::setColor(Color4B color)
{
}

bool LightAttrComponent::isOn()
{
	return 0;
}

void LightAttrComponent::initListeners()
{
}

void LightAttrComponent::onChangeIntensity(EventCustom* pEvent)
{
}

float LightAttrComponent::getIntensity()
{
	return 0;
}

void LightAttrComponent::setIntensity(float intensity)
{
}
}  // namespace Game
