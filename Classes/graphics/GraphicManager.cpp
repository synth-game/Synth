#include "GraphicManager.h"

namespace Graphics
{

GraphicManager::GraphicManager()
{
}

GraphicManager::~GraphicManager()
{
}

GraphicManager* GraphicManager::getInstance()
{
	return 0;
}

void GraphicManager::init(System::xml data)
{
}

Sprite* GraphicManager::createSprite(string sSpriteName)
{
	return 0;
}

Animation* GraphicManager::getAnimation(string sAnimName)
{
	return 0;
}

Animation* GraphicManager::getNextAnimation(string sAnimName)
{
	return 0;
}

boolean GraphicManager::isLoopAnimation(string sAnimName)
{
	return 0;
}
}  // namespace Graphics