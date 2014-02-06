#include "SynthConfig.h"

namespace core
{

SynthConfig::SynthConfig()
{
}

SynthConfig::~SynthConfig()
{
}

SynthConfig* SynthConfig::getInstance()
{
	return 0;
}

void SynthConfig::init(core::xml data)
{
}

xml SynthConfig::getConfig()
{
	xml fakeXml;
	return fakeXml;
}

float SynthConfig::getMusicVolume()
{
	return 0;
}

float SynthConfig::getSoundVolume()
{
	return 0;
}

Language SynthConfig::getLanguage()
{
	return Language::FRENCH;
}

Language SynthConfig::getSubtitleLanguage()
{
	return Language::FRENCH;
}

float SynthConfig::getLuminosity()
{
	return 0;
}

int SynthConfig::getSavedLevel()
{
	return 0;
}

void SynthConfig::setMusicVolume(float musicVolume)
{
}

void SynthConfig::setSoundVolume(float soundVolume)
{
}

void SynthConfig::setLanguage(Language eLanguage)
{
}

void SynthConfig::setSubtitleLanguage(Language eSubtitleLanguage)
{
}

void SynthConfig::setLuminosity(float fLuminosity)
{
}

void SynthConfig::setSavedLevel(int iSavedLevel)
{
}
}  // namespace core
