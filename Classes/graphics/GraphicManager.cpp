/*!
 * \file GraphicManager.h
 * \brief Singleton dealing with the graphics of the game (sprites, images)
 * \author Chupee
 * \date 12/02/2014
 */
#include "GraphicManager.h"

namespace graphics {

GraphicManager::GraphicManager() {
}

GraphicManager::~GraphicManager() {
}

GraphicManager* GraphicManager::getInstance() {
	return 0;
}

void GraphicManager::init(core::xml data) {
}

Sprite* GraphicManager::createSprite(std::string sSpriteName) {
	return 0;
}

Animation* GraphicManager::getAnimation(std::string sAnimName) {
	return 0;
}

Animation* GraphicManager::getNextAnimation(std::string sAnimName) {
	return 0;
}

bool GraphicManager::isLoopAnimation(std::string sAnimName) {
	return 0;
}


}  // namespace graphics
