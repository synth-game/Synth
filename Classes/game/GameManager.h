/* *****************************************************
 *		GameManager.h - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager : public cocos2d::Layer {
public:
	~GameManager();

	static GameManager* create();

	virtual bool init(); // redéfinition de la méthode de Cocos2dx
	virtual void update(float fDt); // pareil
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

protected:
	GameManager();

	cocos2d::Sprite* _pBackground;
	cocos2d::Sprite* _pHero;
};

#endif //__GAME_MANAGER_H__
