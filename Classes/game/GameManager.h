/* *****************************************************
 *		GameManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "core/SynthActor.h"

USING_NS_CC;

class GameManager : public Layer {
public:
	~GameManager();

	static GameManager* create();

	virtual bool init(); // redéfinition de la méthode de Cocos2dx
	virtual void update(float fDt); // pareil
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

protected:
	GameManager();

	Sprite* _pBackground;
	SynthActor* _pHero;
};

#endif //__GAME_MANAGER_H__
