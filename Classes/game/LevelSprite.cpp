/*!
 * \file LevelSprite.cpp
 * \brief Sprite of the level with lights rendering
 * \author Jijidici
 * \date 26/02/2014
 */
#include <sstream>
#include "LevelSprite.h"
#include "game/SHA_level_sprite.h"
#include "game/NodeOwnerComponent.h"
#include "game/SwitchableComponent.h"
#include "graphics/SpriteComponent.h"
#include "sounds/SoundManager.h"

#include "events/ChangeNodeOwnerEvent.h"

namespace game {

LevelSprite::LevelSprite() {
}

LevelSprite::~LevelSprite() {
	for(std::vector<LightTexture*>::iterator it=_lightTextures.begin(); it!=_lightTextures.end(); ++it) {
		delete *it;
		*it = nullptr;
	}
	_lightTextures.clear();
}

LevelSprite* LevelSprite::create(const char* sBackgroundPath) {
	LevelSprite* pRet = new LevelSprite();
	if (pRet != nullptr && pRet->initWithFile(sBackgroundPath)) {
		CCLOG("LevelSprite::create : LevelSprite created");
		pRet->autorelease();
		pRet->setAnchorPoint(Point::ZERO);

		GLProgram* pProgram = new GLProgram();
		pProgram->initWithVertexShaderByteArray(levelSprite_vert, levelSprite_frag);
		pProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		pProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		pProgram->link();
		pProgram->updateUniforms();
		pProgram->use();
		pRet->setShaderProgram(pProgram);

	} else {
		CCLOG("LevelSprite created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void LevelSprite::addLight(int actorID, Texture2D* pTexture, Color4B color, bool bOn) {
	if (_lightTextures.size() < SHA_LIGHT_MAX_COUNT) {
		LightTexture* pLT = new LightTexture();
		pLT->actorID = actorID;
		pLT->pTex = pTexture;
		pLT->col.push_back(static_cast<float>(color.r)/255.f);
		pLT->col.push_back(static_cast<float>(color.g)/255.f);
		pLT->col.push_back(static_cast<float>(color.b)/255.f);
		pLT->col.push_back(static_cast<float>(color.a)/255.f);
		if (bOn == false) {
			pLT->col[3] = 0.f;
		}
		_lightTextures.push_back(pLT);
	} else {
		CCLOG("There already are maximum of lights in LevelSprite. Can't add another one.");
	}
}

void LevelSprite::addLightSwitch(physics::GeometryComponent* pComp) {
	if (pComp != nullptr) {
		_lightSwitches.push_back(pComp);
	} else {
		CCLOG("LevelSprite addLightSwitch :: component is nullptr");
	}
}

void LevelSprite::updateLight(core::SynthActor* pLamp) {
	CCASSERT(pLamp->getActorType() == core::ActorType::LIGHT, "LevelFactory::updateLight. The lamp is not what we thought it is ! KILL IT NOW !");
	game::NodeOwnerComponent* pNodeOwnerComp = static_cast<game::NodeOwnerComponent*>(pLamp->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	game::SwitchableComponent* pSwitchableComp = static_cast<game::SwitchableComponent*>(pLamp->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
	core::SynthActor* firefly = static_cast<core::SynthActor*>(pNodeOwnerComp->getOwnedNode());

	for (auto texture : _lightTextures) {
		if (texture->actorID == pLamp->getActorID()) {
			Color4B color = Color4B(0, 0, 0, 0);
			if(firefly != nullptr && pSwitchableComp->isOn()) {
				switch (firefly->getActorType()) {
				case core::ActorType::RED_FIREFLY:
					color = Color4B::RED;
					break;
				case core::ActorType::GREEN_FIREFLY:
					color = Color4B::GREEN;
					break;
				case core::ActorType::BLUE_FIREFLY:
					color = Color4B::BLUE;
					break;
				default:
					break;
				}
			}

			texture->col[0] = static_cast<float>(color.r)/255.f;
			texture->col[1] = static_cast<float>(color.g)/255.f;
			texture->col[2] = static_cast<float>(color.b)/255.f;
			texture->col[3] = static_cast<float>(color.a)/255.f;
		}
	}
}

void LevelSprite::draw() {
	_shaderProgram->use();
	_shaderProgram->setUniformLocationWith2f(_shaderProgram->getUniformLocationForName("SY_LevelPixelSize"), 1.f/_contentSize.width, 1.f/_contentSize.height);

	int iLightOnCount = 0;
	for(unsigned int i=0; i<_lightTextures.size(); ++i) {
		if(_lightTextures[i]->col[3] > 0.0001f) {
			std::stringstream lightLocation;
			lightLocation << "SY_Lights_" << iLightOnCount;
			_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName(lightLocation.str().c_str()), iLightOnCount+1);

			std::stringstream colorLocation;
			colorLocation << "SY_Colors["<<iLightOnCount<<"]";
			_shaderProgram->setUniformLocationWith4fv(_shaderProgram->getUniformLocationForName(colorLocation.str().c_str()), &(_lightTextures[i]->col[0]), 1);

			GL::bindTexture2DN(iLightOnCount+1, _lightTextures[i]->pTex->getName());
			++iLightOnCount;
		}
	}
	_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName("SY_LightCount"), iLightOnCount);

	Sprite::draw();

	GL::bindTexture2DN(1, 0);
	for(unsigned int i=0; i<_lightTextures.size(); ++i) {
		GL::bindTexture2DN(i+1, 0);
	}

	for (auto lightSwitch : _lightSwitches) {
		Point origin = Point(lightSwitch->getPosition().x - (lightSwitch->getSize().width/2), lightSwitch->getPosition().y);
		Point destination = Point(lightSwitch->getPosition().x+(lightSwitch->getSize().width/2), lightSwitch->getPosition().y+(lightSwitch->getSize().height));
		DrawPrimitives::drawSolidRect(origin, destination, Color4F::BLACK);
	}

}

// this method doesnt listen the event, it is called by the node owner component
void LevelSprite::onChangeNodeOwner(EventCustom* pEvent, core::SynthActor* pOwner) {
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent			= static_cast<events::ChangeNodeOwnerEvent*>(pEvent);
	core::SynthActor* pNewOwner									= static_cast<core::SynthActor*>(pChangeNodeOwnerEvent->getNewOwner());
	core::SynthActor* pPreviousOwner							= static_cast<core::SynthActor*>(pChangeNodeOwnerEvent->getPreviousOwner());
	core::SynthActor* pSource									= static_cast<core::SynthActor*>(pChangeNodeOwnerEvent->getOwned());

	if(pNewOwner != nullptr && pNewOwner->getActorID() == pOwner->getActorID()) {
		// if a firefly goes to a light
		if ( pSource->isFirefly() && pNewOwner != nullptr && pNewOwner->getActorType() == core::ActorType::LIGHT ) {
			game::SwitchableComponent* pSwitchableComp = dynamic_cast<game::SwitchableComponent*>(pNewOwner->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
			if (pSwitchableComp != nullptr) {
				pSwitchableComp->setOn(true);
				updateLight(pNewOwner);
			}
		}
		// if a firefly leaves a light
		if (pSource->isFirefly() && pPreviousOwner != nullptr && pPreviousOwner->getActorType() == core::ActorType::LIGHT ) {
			game::SwitchableComponent* pSwitchableComp = dynamic_cast<game::SwitchableComponent*>(pPreviousOwner->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
			if (pSwitchableComp != nullptr) {
				pSwitchableComp->setOn(false);
				updateLight(pPreviousOwner);
			}
		}
	}

}

}  // namespace game
