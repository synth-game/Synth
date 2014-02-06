#include "SpriteComponent.h"


namespace graphics
{
char* SpriteComponent::COMPONENT_TYPE;

SpriteComponent::SpriteComponent()
{

}

SpriteComponent::~SpriteComponent()
{
}

bool SpriteComponent::init() {
    return true;
}

SpriteComponent* SpriteComponent::create(std::string sSpriteName, Layer* pParent) {
	return nullptr;
}

void SpriteComponent::initListeners()
{
}

void SpriteComponent::onEditMove(EventCustom* pEvent)
{
}
}  // namespace graphics
