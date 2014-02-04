#ifndef GRAPHICS_TEXT_SPRITE_COMPONENT_H
#define GRAPHICS_TEXT_SPRITE_COMPONENT_H

#include "EventCustom.h"
#include "Graphics/SpriteComponent.h"
#include "Graphics/LabelTTF.h"

namespace Graphics
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
	static TextSpriteComponent* create(string sText, char* sFontName, float fFontSize);

	string getText();

	void setText(string sText);

};

}  // namespace Graphics
#endif
