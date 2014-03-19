/*!
 * \file LightMap.cpp
 * \brief Array of lighting using for physical light collision
 * \author Jijidici
 * \date 10/03/2014
 */
#include "game/LightMap.h"
#include "game/LightAttrComponent.h"
#include "game/NodeOwnerComponent.h"
#include "game/SwitchableComponent.h"
#include "sounds/SoundManager.h"
#include "events/ChangeNodeOwnerEvent.h"

namespace game {

LightMap::LightMap()
	: _iW(0)
	, _iH(0)
	, _iResolutionCoef(1) {
}

LightMap::~LightMap() {
	_pixelGrid.clear();
}

LightMap* LightMap::createFromXML(std::string sFilePath) {
	LightMap* pRet = new LightMap();
	if (pRet != nullptr) {
		
		// load xml file
		tinyxml2::XMLDocument doc;
		int xmlerror = doc.LoadFile(sFilePath.c_str());
		CCASSERT(xmlerror == 0, "ERROR WHILE LOADING LIGHTMAP XML FILE");

		tinyxml2::XMLElement* pRootElt = doc.FirstChildElement("root");
		pRet->_iW = pRootElt->IntAttribute("width");
		pRet->_iH = pRootElt->IntAttribute("height");
		pRet->_iResolutionCoef = pRootElt->IntAttribute("resolution_coef");

		// fill the pixel map
		Color4B noColor = Color4B::BLACK;
		noColor.a = 0;

		tinyxml2::XMLElement* pPixelElt = pRootElt->FirstChildElement("pixel");
		while (pPixelElt != nullptr) {
			int index = pPixelElt->IntAttribute("array_index");
			std::vector<std::pair<int, bool>> lightSamples;

			tinyxml2::XMLElement* pLightSampleElt = pPixelElt->FirstChildElement("light_sample");
			while (pLightSampleElt != nullptr) {
				std::pair<int, bool> sample;
				sample.first = pLightSampleElt->IntAttribute("id");
				sample.second = pLightSampleElt->BoolAttribute("occulted");
				lightSamples.push_back(sample);

				pLightSampleElt = pLightSampleElt->NextSiblingElement("light_sample");
			}
			pRet->_pixelGrid.insert(std::make_pair(index, std::make_pair(noColor, lightSamples)));

			pPixelElt = pPixelElt->NextSiblingElement("pixel");
		}

    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void LightMap::fastUpdate(core::SynthActor* pLight, std::vector<core::SynthActor*>& lights) {
	int iLightIndex = -1;
	for(unsigned int i=0; i<lights.size(); ++i) {
		if(lights[i] == pLight) {
			iLightIndex = static_cast<int>(i);
			break;
		}
	}

	if(iLightIndex != -1) {
		for(auto itPix=_pixelGrid.begin(); itPix!=_pixelGrid.end(); ++itPix) {
			std::vector<std::pair<int, bool>> currentPixel = itPix->second.second;

			bool bUpdateThisPIxel = false;
			for (auto itSample=currentPixel.begin(); itSample!=currentPixel.end(); ++itSample) {
				if (iLightIndex == itSample->first) {
					bUpdateThisPIxel = true;
					break;
				}
			}

			if (bUpdateThisPIxel) {
				Color4B occultedColor(0, 0, 0, 0);
				Color4B notOccultedColor(0, 0, 0, 0);

				for (auto itSample=currentPixel.begin(); itSample!=currentPixel.end(); ++itSample) {
					if(itSample->first < lights.size()) {
						Color4B lightColor = Color4B(0, 0, 0, 0);
						core::SynthActor* currentLight = lights[itSample->first];
						game::NodeOwnerComponent* pNodeOwnerComp = static_cast<game::NodeOwnerComponent*>(currentLight->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
						game::SwitchableComponent* pSwitchableComp = static_cast<game::SwitchableComponent*>(currentLight->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
						core::SynthActor* firefly = static_cast<core::SynthActor*>(pNodeOwnerComp->getOwnedNode());
						if(firefly != nullptr && pSwitchableComp->isOn()) {
							switch (firefly->getActorType()) {
							case core::ActorType::RED_FIREFLY:
								lightColor = Color4B::RED;
								break;
							case core::ActorType::GREEN_FIREFLY:
								lightColor = Color4B::GREEN;
								break;
							case core::ActorType::BLUE_FIREFLY:
								lightColor = Color4B::BLUE;
								break;
							default:
								break;
							}
						}

						if (notOccultedColor.r == 255 || lightColor.r == 255) { notOccultedColor.r = 255; }
						if (notOccultedColor.g == 255 || lightColor.g == 255) { notOccultedColor.g = 255; }
						if (notOccultedColor.b == 255 || lightColor.b == 255) { notOccultedColor.b = 255; }
						notOccultedColor.a = 255;

						// check if the pixel is occulted from the light
						if (itSample->second == false) {
							if (occultedColor.r == 255 || lightColor.r == 255) { occultedColor.r = 255; }
							if (occultedColor.g == 255 || lightColor.g == 255) { occultedColor.g = 255; }
							if (occultedColor.b == 255 || lightColor.b == 255) { occultedColor.b = 255; }
							occultedColor.a = 255;
						}
					}
				}

				if (notOccultedColor.r == 255 && notOccultedColor.g == 255 && notOccultedColor.b == 255) {
					itPix->second.first = Color4B::WHITE;
				} else {
					itPix->second.first = occultedColor;
				}
			}
		}
	}
}

void LightMap::updateLighting(std::vector<core::SynthActor*>& lights) {
	for(auto itPix=_pixelGrid.begin(); itPix!=_pixelGrid.end(); ++itPix) {

		std::vector<std::pair<int, bool>> currentPixel = itPix->second.second;
		if (!currentPixel.empty()) {
			Color4B occultedColor(0, 0, 0, 0);
			Color4B notOccultedColor(0, 0, 0, 0);

			for (std::vector<std::pair<int, bool>>::iterator itSample=currentPixel.begin(); itSample!=currentPixel.end(); ++itSample) {
				if(itSample->first < lights.size()) {
					Color4B lightColor = Color4B(0, 0, 0, 0);
					core::SynthActor* currentLight = lights[itSample->first];

					game::NodeOwnerComponent* pNodeOwnerComp = static_cast<game::NodeOwnerComponent*>(currentLight->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
					game::SwitchableComponent* pSwitchableComp = static_cast<game::SwitchableComponent*>(currentLight->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
					core::SynthActor* firefly = static_cast<core::SynthActor*>(pNodeOwnerComp->getOwnedNode());
					if(firefly != nullptr && pSwitchableComp->isOn()) {
						switch (firefly->getActorType()) {
						case core::ActorType::RED_FIREFLY:
							lightColor = Color4B::RED;
							break;
						case core::ActorType::GREEN_FIREFLY:
							lightColor = Color4B::GREEN;
							break;
						case core::ActorType::BLUE_FIREFLY:
							lightColor = Color4B::BLUE;
							break;
						default:
							break;
						}
					}

					if (notOccultedColor.r == 255 || lightColor.r == 255) { notOccultedColor.r = 255; }
					if (notOccultedColor.g == 255 || lightColor.g == 255) { notOccultedColor.g = 255; }
					if (notOccultedColor.b == 255 || lightColor.b == 255) { notOccultedColor.b = 255; }
					notOccultedColor.a = 255;

					// check if the pixel is occulted from the light
					if (itSample->second == false) {
						if (occultedColor.r == 255 || lightColor.r == 255) { occultedColor.r = 255; }
						if (occultedColor.g == 255 || lightColor.g == 255) { occultedColor.g = 255; }
						if (occultedColor.b == 255 || lightColor.b == 255) { occultedColor.b = 255; }
						occultedColor.a = 255;
					}
				}
			}

			if (notOccultedColor.r == 255 && notOccultedColor.g == 255 && notOccultedColor.b == 255) {
				itPix->second.first = Color4B::WHITE;
			} else {
				itPix->second.first = occultedColor;
			}
		}
		sounds::SoundManager* soundManager = sounds::SoundManager::getInstance();
		soundManager->updateMusics(itPix->second.first);
	}
}

void LightMap::onChangeNodeOwner(EventCustom* pEvent, core::SynthActor* pOwner, std::vector<core::SynthActor*>& lights) {
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
				fastUpdate(pNewOwner, lights);
			}
		}
		// if a firefly leaves a light
		if (pSource->isFirefly() && pPreviousOwner != nullptr && pPreviousOwner->getActorType() == core::ActorType::LIGHT ) {
			game::SwitchableComponent* pSwitchableComp = dynamic_cast<game::SwitchableComponent*>(pPreviousOwner->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
			if (pSwitchableComp != nullptr) {
				pSwitchableComp->setOn(false);
				fastUpdate(pPreviousOwner, lights);
			}
		}
	}
}

Color4B LightMap::getPixelLighting(Point absPos) {
	Color4B colorRet(0,0,0,0);
	
	int iX = static_cast<int>(absPos.x/_iResolutionCoef);
	int iY = _iH - static_cast<int>(absPos.y/_iResolutionCoef);

	if (iX>=0 && iX<_iW && iY>=0 && iY<_iH) {
		auto itPix = _pixelGrid.find(iX + iY*_iW);
		if (itPix != _pixelGrid.end()) {
			colorRet = itPix->second.first;
		}
	}

	return colorRet;
}

}	// namespace game