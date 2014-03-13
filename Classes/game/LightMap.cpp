/*!
 * \file LightMap.cpp
 * \brief Array of lighting using for physical light collision
 * \author Jijidici
 * \date 10/03/2014
 */
#include "game/LightMap.h"
#include "game/LightAttrComponent.h"
#include "sounds/SoundManager.h"

namespace game {

LightMap::LightMap()
	: _iW(0)
	, _iH(0)
	, _iResolutionCoef(0) {
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

		// initialize pixel map
		pRet->_pixelGrid.resize(pRet->_iW*pRet->_iH);
		Color4B noColor = Color4B::BLACK;
		noColor.a = 0;
		for(int i=0; i<pRet->_iW*pRet->_iH; ++i) {
			pRet->_pixelGrid[i] = std::make_pair(noColor, std::vector<std::pair<int, bool>>());
		}

		// fill the pixel map
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
			pRet->_pixelGrid[index].second = lightSamples;

			pPixelElt = pPixelElt->NextSiblingElement("pixel");
		}

    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void LightMap::updateLighting(std::vector<core::SynthActor*>& lights) {

	for (int i=0; i<_iW*_iH; ++i) {
		
		std::vector<std::pair<int, bool>> currentPixel = _pixelGrid[i].second;

		if (currentPixel.size() > 0) {
			Color4B occultedColor(0, 0, 0, 0);
			Color4B notOccultedColor(0, 0, 0, 0);

			for (std::vector<std::pair<int, bool>>::iterator itSample=currentPixel.begin(); itSample!=currentPixel.end(); ++itSample) {
				if (itSample->first <3){ // test
					core::SynthActor* currentLight = lights[itSample->first];
					LightAttrComponent* pLightAttrComp =  dynamic_cast<LightAttrComponent*>(currentLight->getComponent(LightAttrComponent::COMPONENT_TYPE));
					CCASSERT(pLightAttrComp != nullptr, "A SynthActor sent to update LightMap hasn't got a LightAttrComponent. It's not a light !");

					Color4B lightColor = pLightAttrComp->getColor();
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
				_pixelGrid[i].first = Color4B::WHITE;
			} else {
				_pixelGrid[i].first = occultedColor;
			}
		}
		sounds::SoundManager* soundManager = sounds::SoundManager::getInstance();
		//soundManager->updateMusics(_pixelGrid[i].first);
	}
}

Color4B LightMap::getPixelLighting(Point absPos) {
	Color4B colorRet(0,0,0,0);
	
	int iX = static_cast<int>(absPos.x/_iResolutionCoef);
	int iY = _iH - static_cast<int>(absPos.y/_iResolutionCoef);

	if (iX < _iW && iY < _iH) {
		colorRet = _pixelGrid[iX + iY*_iW].first;
	}

	return colorRet;
}

}	// namespace game