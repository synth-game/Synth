#ifndef GRAPHICS_GRAPHIC_MANAGER_H
#define GRAPHICS_GRAPHIC_MANAGER_H

#include "vector.h"
#include "Actor.h"
#include "map.h"
#include "Animation.h"
#include "Graphics/Sprite.h"
#include "System/xml.h"

namespace Graphics
{
class GraphicManager
{
private:
	vector<Actor*> _staticSprites;

	map<string,Animation> _animations;


private:
	GraphicManager();

public:
	~GraphicManager();

	static GraphicManager* getInstance();

	/**
	 * ! Don't forget to load all animations after building data vector
	 * 
	 */
	void init(System::xml data);

	Sprite* createSprite(string sSpriteName);

	Animation* getAnimation(string sAnimName);

	/**
	 * return null if requested animation isn't chained
	 */
	Animation* getNextAnimation(string sAnimName);

	boolean isLoopAnimation(string sAnimName);

};

}  // namespace Graphics
#endif
