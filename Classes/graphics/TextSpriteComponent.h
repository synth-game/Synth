#ifndef GRAPHICS_TEXT_SPRITE_COMPONENT_H
#define GRAPHICS_TEXT_SPRITE_COMPONENT_H


#include "Graphics/SpriteComponent.h"
#include "Graphics/LabelTTF.h"

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
