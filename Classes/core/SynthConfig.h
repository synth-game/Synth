#ifndef CORE_SYNTH_CONFIG_H
#define CORE_SYNTH_CONFIG_H

#include "Core/Language.h"
#include "System/xml.h"

namespace core
{
class SynthConfig
{
private:
	float _fMusicVolume;

	float _fSoundVolume;

	Language _eLanguage;

	Language _eSubtitleLanguage;

	float _fLuminosity;

	int _iSavedLevel;


private:
	/**
	 *
	 */
	SynthConfig();

public:
	/**
	 *
	 */
	~SynthConfig();

	static SynthConfig* getInstance();

	void init(system::xml data);

	system::xml getConfig();

	/**
	 *
	 */
	float getMusicVolume();

	/**
	 *
	 */
	float getSoundVolume();

	/**
	 *
	 */
	Language getLanguage();

	/**
	 *
	 */
	Language getSubtitleLanguage();

	/**
	 *
	 */
	float getLuminosity();

	/**
	 *
	 */
	int getSavedLevel();

	/**
	 *
	 */
	void setMusicVolume(float musicVolume);

	/**
	 *
	 */
	void setSoundVolume(float soundVolume);

	/**
	 *
	 */
	void setLanguage(Language eLanguage);

	/**
	 *
	 */
	void setSubtitleLanguage(Language eSubtitleLanguage);

	/**
	 *
	 */
	void setLuminosity(float fLuminosity);

	/**
	 *
	 */
	void setSavedLevel(int iSavedLevel);

};

}  // namespace core
#endif
