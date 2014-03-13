/*!
 * \file SynthConfig.h
 * \brief Singleton managing with the game config
 * \author Chupee
 * \date 13/03/2014
 */
#ifndef CORE_SYNTH_CONFIG_H
#define CORE_SYNTH_CONFIG_H

#include "cocos2d.h"
#include "Core/Language.h"

namespace core {


/*! \class SynthConfig
 * \brief Singleton managing with the game config
 *
 *
 */
class SynthConfig {

public:

	~SynthConfig();

	static SynthConfig* getInstance();

	void init();

	tinyxml2::XMLDocument* getConfig();

	float getMusicVolume();

	float getSoundVolume();

	Language getLanguage();

	Language getSubtitleLanguage();

	float getLuminosity();

	int getSavedLevel();

	void setMusicVolume(float musicVolume);

	void setSoundVolume(float soundVolume);

	void setLanguage(Language eLanguage);

	void setSubtitleLanguage(Language eSubtitleLanguage);

	void setLuminosity(float fLuminosity);

	void setSavedLevel(int iSavedLevel);

private:

	SynthConfig();

	static SynthConfig* _pInstance;

	float _fMusicVolume;

	float _fSoundVolume;

	Language _eLanguage;

	Language _eSubtitleLanguage;

	float _fLuminosity;

	int _iSavedLevel;

};

}  // namespace core
#endif
