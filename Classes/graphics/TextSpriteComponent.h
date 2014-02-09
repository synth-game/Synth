#ifndef GRAPHICS_TEXT_SPRITE_COMPONENT_H
#define GRAPHICS_TEXT_SPRITE_COMPONENT_H

#include "cocos2d.h"
#include "Graphics/SpriteComponent.h"

USING_NS_CC;

namespace graphics
{
class TextSpriteComponent : public SpriteComponent
{
protected:
	LabelTTF* _pLabel;

	EventCustom* _pToggleTextListener;


protected:
	/**
	 *
	 */
	TextSpriteComponent();

	/**
	 *
	 */
	void onToggleText(EventCustom* pEvent);

public:
	/**
	 *
	 */
	~TextSpriteComponent();

	/**
	 *
	 */
	static TextSpriteComponent* create(std::string sText, char* sFontName, float fFontSize);

	std::string getText();

	void setText(std::string sText);

};

}  // namespace graphics
#endif
