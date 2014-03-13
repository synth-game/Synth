/*!
 * \file SynthConfig.cpp
 * \brief Singleton managing with the game config
 * \author Chupee
 * \date 13/03/2014
 */
#include "SynthConfig.h"
#include "system/IOManager.h"
#include "game/GameManager.h"

namespace core {

static SynthConfig* _pInstance = nullptr;

SynthConfig::SynthConfig() {
}

SynthConfig::~SynthConfig() {
}

SynthConfig* SynthConfig::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new SynthConfig();
    }
	return _pInstance;
}

void SynthConfig::init() {
	
}

tinyxml2::XMLDocument* SynthConfig::getConfig() {
	return synthsystem::IOManager::getInstance()->loadXML("xml/save.xml");
}

void SynthConfig::saveConfig(tinyxml2::XMLDocument* save) {
	if(save != nullptr) {
		synthsystem::IOManager::getInstance()->saveXML("xml/save.xml", save);
	}
}

float SynthConfig::getMusicVolume() {
	return 0;
}

float SynthConfig::getSoundVolume() {
	return 0;
}

Language SynthConfig::getLanguage() {
	return Language::FRENCH;
}

Language SynthConfig::getSubtitleLanguage() {
	return Language::FRENCH;
}

float SynthConfig::getLuminosity() {
	return 0;
}

int SynthConfig::getCurrentLevelIndex() {
	tinyxml2::XMLDocument* save = getConfig();
	tinyxml2::XMLDocument* levels = synthsystem::IOManager::getInstance()->loadXML("xml/levels.xml");

	tinyxml2::XMLElement* pLevelData = save->FirstChildElement("level");
	tinyxml2::XMLElement* level = levels->FirstChildElement("level"); 
	int count = 0;
	while (level) {
		level = level->NextSiblingElement();  
		++count;
	}
	
	tinyxml2::XMLElement *pLevelData = save->FirstChildElement("level");
	
	int levelIndex = -1;
	levelIndex = pLevelData->IntAttribute("index");
	if(levelIndex > 0 && levelIndex <= count ) {
		return levelIndex;
	}
	return 0;
}

void SynthConfig::setMusicVolume(float musicVolume) {
}

void SynthConfig::setSoundVolume(float soundVolume) {
}

void SynthConfig::setLanguage(Language eLanguage) {
}

void SynthConfig::setSubtitleLanguage(Language eSubtitleLanguage) {
}

void SynthConfig::setLuminosity(float fLuminosity) {
}

void SynthConfig::setSavedLevel(int iSavedLevel) {
}

}  // namespace core
