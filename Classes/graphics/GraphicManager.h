#ifndef GRAPHICS_GRAPHIC_MANAGER_H
#define GRAPHICS_GRAPHIC_MANAGER_H

#include <vector>
#include "Actor.h"
#include <map>
#include "Animation.h"
#include "Graphics/Sprite.h"
#include "System/xml.h"

namespace graphics
{
class GraphicManager
{
private:
	std::vector<Actor*> _staticSprites;

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
	void init(system::xml data);

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
