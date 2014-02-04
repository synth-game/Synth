#ifndef CORE_TEXT_MANAGER_H
#define CORE_TEXT_MANAGER_H

#include "map.h"
#include "Core/Language.h"
#include "System/xml.h"

namespace Core
{
class TextManager
{
private:
	/**
	 * The big data structure :
	 * 
	 * Contains for each language, the real text string associated to a text tag
	 * the first string is the tag, the second one the real text
	 */
	map<Language,vector<Actor*> , map<string,string>> _textSamples;


private:
	TextManager();

public:
	~TextManager();

	static TextManager* getInstance();

	void init(System::xml data);

	string getText(string TextTag);

};

}  // namespace Core
#endif
