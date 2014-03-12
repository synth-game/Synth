#ifndef OPENAL

#include "SynthSimpleAudioEngine.h"
#include "SynthFmodAudioPlayer.h"
#include "cocos2d.h"
USING_NS_CC;

namespace core {

static SynthAudioPlayer* oAudioPlayer;

SynthSimpleAudioEngine::SynthSimpleAudioEngine() {
    oAudioPlayer = SynthFmodAudioPlayer::sharedPlayer();
}

SynthSimpleAudioEngine::~SynthSimpleAudioEngine() {
}

SynthSimpleAudioEngine* SynthSimpleAudioEngine::getInstance() {
    static SynthSimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SynthSimpleAudioEngine::end() {
    oAudioPlayer->close();
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SynthSimpleAudioEngine::playBackgroundMusic(const char* pszFilePath,
        bool bLoop) {
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
    oAudioPlayer->playBackgroundMusic(fullPath.c_str(), bLoop);
}

void SynthSimpleAudioEngine::stopBackgroundMusic(bool bReleaseData) {
    oAudioPlayer->stopBackgroundMusic(bReleaseData);
}

void SynthSimpleAudioEngine::pauseBackgroundMusic() {
    oAudioPlayer->pauseBackgroundMusic();
}

void SynthSimpleAudioEngine::resumeBackgroundMusic() {
    oAudioPlayer->resumeBackgroundMusic();
}

void SynthSimpleAudioEngine::rewindBackgroundMusic() {
    oAudioPlayer->rewindBackgroundMusic();
}

bool SynthSimpleAudioEngine::willPlayBackgroundMusic() {
    return oAudioPlayer->willPlayBackgroundMusic();
}

bool SynthSimpleAudioEngine::isBackgroundMusicPlaying() {
    return oAudioPlayer->isBackgroundMusicPlaying();
}

void SynthSimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath) {
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
    return oAudioPlayer->preloadBackgroundMusic(fullPath.c_str());
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SynthSimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,
                                           float pitch, float pan, float gain) {
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
    return oAudioPlayer->playEffect(fullPath.c_str(), bLoop, pitch, pan, gain);
}

void SynthSimpleAudioEngine::stopEffect(unsigned int nSoundId) {
    return oAudioPlayer->stopEffect(nSoundId);
}

void SynthSimpleAudioEngine::preloadEffect(const char* pszFilePath) {
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
    return oAudioPlayer->preloadEffect(fullPath.c_str());
}

void SynthSimpleAudioEngine::unloadEffect(const char* pszFilePath) {
    // Changing file path to full path
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(pszFilePath);
    return oAudioPlayer->unloadEffect(fullPath.c_str());
}

void SynthSimpleAudioEngine::pauseEffect(unsigned int uSoundId) {
    oAudioPlayer->pauseEffect(uSoundId);
}

void SynthSimpleAudioEngine::pauseAllEffects() {
    oAudioPlayer->pauseAllEffects();
}

void SynthSimpleAudioEngine::resumeEffect(unsigned int uSoundId) {
    oAudioPlayer->resumeEffect(uSoundId);
}

void SynthSimpleAudioEngine::resumeAllEffects() {
    oAudioPlayer->resumeAllEffects();
}

void SynthSimpleAudioEngine::stopAllEffects() {
    oAudioPlayer->stopAllEffects();
}



//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SynthSimpleAudioEngine::getBackgroundMusicVolume() {
    return oAudioPlayer->getBackgroundMusicVolume();
}

void SynthSimpleAudioEngine::setBackgroundMusicVolume(float volume) {
    return oAudioPlayer->setBackgroundMusicVolume(volume);
}

float SynthSimpleAudioEngine::getEffectsVolume() {
    return oAudioPlayer->getEffectsVolume();
}

void SynthSimpleAudioEngine::setEffectsVolume(float volume) {
    return oAudioPlayer->setEffectsVolume(volume);
}


} // end of namespace core

#endif
