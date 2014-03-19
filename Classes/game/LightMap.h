/*!
 * \file LightMap.h
 * \brief Array of lighting using for physical light collision
 * \author Jijidici
 * \date 10/03/2014
 */
#ifndef GAME_LIGHT_MAP_H
#define GAME_LIGHT_MAP_H

#include <map>
#include <utility>
#include <string>
#include "cocos2d.h"
#include "core/SynthActor.h"

USING_NS_CC;

namespace game {

/*! \class LightMap
 * \brief Array of lighting using for physical light collision
 */
class LightMap {
public:
	/*! \brief Destructor */
	~LightMap();
	static LightMap* createFromXML(std::string sFilePath);

	inline int getWidth() { return _iW; };
	inline int getHeight() { return _iH; };
	inline std::map<int,std::pair<Color4B, std::vector<std::pair<int, bool>>>>& getPixelGrid() { return _pixelGrid; };

	void fastUpdate(core::SynthActor* pLight, std::vector<core::SynthActor*>& lights);
	void updateLighting(std::vector<core::SynthActor*>& lights);
	Color4B getPixelLighting(Point absPos);
	void onChangeNodeOwner(EventCustom* pEvent, core::SynthActor* pOwner, std::vector<core::SynthActor*>& lights);

protected:
	/*! \brief Constructor */
	LightMap();

	int _iW;
	int _iH;
	int _iResolutionCoef;
	std::map<int,std::pair<Color4B, std::vector<std::pair<int, bool>>>> _pixelGrid;
};

}	// namespace game

#endif //GAME_LIGHT_MAP_H