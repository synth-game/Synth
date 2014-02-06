#ifndef GRAPHICS_GRAPHIC_MANAGER_H
#define GRAPHICS_GRAPHIC_MANAGER_H

#include <vector>
#include <map>
#include "cocos2d.h"
#include "core/SynthActor.h"
#include "core/SynthConfig.h"

USING_NS_CC;



namespace graphics
{
class GraphicManager
{
private:
	std::vector<core::SynthActor*> _staticSprites;

	std::map<std::string,Animation> _animations;


private:
	GraphicManager();

public:
	~GraphicManager();

	static GraphicManager* getInstance();

	/**
	 * ! Don't forget to load all animations after building data vector
	 *
	 */
	void init(core::xml data);

	Sprite* createSprite(std::string sSpriteName);

	Animation* getAnimation(std::string sAnimName);

	/**
	 * return null if requested animation isn't chained
	 */
	Animation* getNextAnimation(std::string sAnimName);

	bool isLoopAnimation(std::string sAnimName);

};

}  // namespace graphics
#endif
