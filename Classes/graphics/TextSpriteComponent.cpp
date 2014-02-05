#include "TextSpriteComponent.h"

namespace graphics
{

TextSpriteComponent::TextSpriteComponent()
{
}

TextSpriteComponent::~TextSpriteComponent()
{
}

TextSpriteComponent* TextSpriteComponent::create(std::string sText, char* sFontName, float fFontSize)
{
	return 0;
}

std::string TextSpriteComponent::getText()
{
	return 0;
}

void TextSpriteComponent::setText(std::string sText)
{
}

void TextSpriteComponent::onToggleText(EventCustom* pEvent)
{
}
}  // namespace graphics
