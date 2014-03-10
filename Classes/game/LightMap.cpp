/*!
 * \file LightMap.cpp
 * \brief Array of lighting using for physical light collision
 * \author Jijidici
 * \date 10/03/2014
 */
#include "game/LightMap.h"

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
		while(pPixelElt != nullptr) {
			int index = pPixelElt->IntAttribute("array_index");
			std::vector<std::pair<int, bool>> lightSamples;

			tinyxml2::XMLElement* pLightSampleElt = pPixelElt->FirstChildElement("light_sample");
			while(pLightSampleElt != nullptr) {
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

}	// namespace game