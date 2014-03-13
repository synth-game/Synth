/*!
 * \file SynthConfig.cpp
 * \brief Singleton managing with the game config
 * \author Chupee
 * \date 13/03/2014
 */
#include "SynthConfig.h"

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
	tinyxml2::XMLDocument* fakeXml;
	return fakeXml;
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

int SynthConfig::getSavedLevel() {
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
