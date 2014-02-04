#include "SpriteComponent.h"

namespace Graphics
{
char* SpriteComponent::COMPONENT_TYPE;

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent()
{
}

boolean SpriteComponent::init()
{
	return 0;
}

SpriteComponent* SpriteComponent::create(string sSpriteName, Layer parent)
{
	return 0;
}

void SpriteComponent::initListeners()
{
}

void SpriteComponent::onEditMove(EventCustom* pEvent)
{
}
}  // namespace Graphics
