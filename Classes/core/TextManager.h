#ifndef CORE_TEXT_MANAGER_H
#define CORE_TEXT_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include "core/Language.h"
#include "core/SynthActor.h"

class xml;

namespace core
{
class TextManager
{
private:
	/**
	 * The big data structure :
	 *
	 * Contains for each language, the real text std::string associated to a text tag
	 * the first std::string is the tag, the second one the real text
	 */
	std::map<Language,std::vector<core::SynthActor*> , std::map<std::string,std::string>> _textSamples;


private:
	TextManager();

public:
	~TextManager();

	static TextManager* getInstance();

	void init(xml data);

	std::string getText(std::string TextTag);

};

}  // namespace core
#endif
