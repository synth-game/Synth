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
		doc.LoadFile(sFilePath.c_str());

    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

}	// namespace game