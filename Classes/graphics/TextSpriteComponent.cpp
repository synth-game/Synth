#include "TextSpriteComponent.h"

namespace graphics
{

TextSpriteComponent::TextSpriteComponent()
{
}

TextSpriteComponent::~TextSpriteComponent()
{
}

TextSpriteComponent* TextSpriteComponent::create(string sText, char* sFontName, float fFontSize)
{
	return 0;
}

string TextSpriteComponent::getText()
{
	return 0;
}

void TextSpriteComponent::setText(string sText)
{
}

void TextSpriteComponent::onToggleText(EventCustom* pEvent)
{
}
}  // namespace graphics
