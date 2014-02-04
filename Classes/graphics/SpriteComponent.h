/* *****************************************************
 *		SpriteComponent.h - @ Damaris Ankou - 30/01/14
 ***************************************************** */

#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include <string>
#include "cocos2d.h"
#include "core/SynthComponent.h"

USING_NS_CC;

class SpriteComponent : public SynthComponent {

public:
	~SpriteComponent();
	virtual bool init();
	static SpriteComponent* create(std::string sFilePath, Layer* pParentLayer);

	static const char* COMPONENT_TYPE;

protected:
	SpriteComponent();
	virtual void initListeners();
	void onChangePosition(EventCustom* pEvent);
	
	std::string _sFilePath;
	Sprite* _pSprite;
	Layer* _pParentLayer;
	EventListenerCustom* _pChangePositionListener;

};

#endif // __SPRITE_COMPONENT_H__