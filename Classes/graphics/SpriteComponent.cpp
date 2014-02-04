/* *****************************************************
 *      SpriteComponent.cpp - @ Damaris Ankou - 30/01/14
 ***************************************************** */

#include "SpriteComponent.h"

const char* SpriteComponent::COMPONENT_TYPE = "SpriteComponent";

namespace Graphics
{
char* SpriteComponent::COMPONENT_TYPE;

SpriteComponent::SpriteComponent()
    : SynthComponent()
    , _sFilePath()
    , _pSprite(nullptr)
    , _pParentLayer(nullptr) {

}

SpriteComponent::~SpriteComponent()
{
}

bool SpriteComponent::init() {
    SynthComponent::init(SpriteComponent::COMPONENT_TYPE);
    _pSprite = Sprite::create(_sFilePath.c_str());
    _pParentLayer->addChild(_pSprite);
    return true;
}

SpriteComponent* SpriteComponent::create(std::string sFilePath, Layer* pParentLayer) {
    SpriteComponent* pRet = new SpriteComponent();
    if (pRet != nullptr) {
        pRet->autorelease();
        pRet->_sFilePath = sFilePath;
        pRet->_pParentLayer = pParentLayer;
        pRet->init();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void SpriteComponent::initListeners()
{
}

void SpriteComponent::onEditMove(EventCustom* pEvent)
{
}
}  // namespace Graphics
