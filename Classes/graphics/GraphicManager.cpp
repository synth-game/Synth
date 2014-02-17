/*!
 * \file GraphicManager.h
 * \brief Singleton dealing with the graphics of the game (sprites, images)
 * \author Chupee
 * \date 12/02/2014
 */
#include "GraphicManager.h"

namespace graphics {

GraphicManager* GraphicManager::_pInstance = nullptr;

GraphicManager::GraphicManager() {
}

GraphicManager::~GraphicManager() {
}

GraphicManager* GraphicManager::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new GraphicManager();
    }
	return _pInstance;
}

void GraphicManager::init(core::xml data) {
}

Sprite* GraphicManager::createSprite(std::string sSpriteName) {
	// Create sprite
	Sprite* pSprite = Sprite::create(sSpriteName.c_str());
	pSprite->setAnchorPoint(Point(0.f, 1.f));
	pSprite->setPosition(Point(0.f, pSprite->getContentSize().height));
	return pSprite;
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
