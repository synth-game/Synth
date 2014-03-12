/*
 * FmodAudioPlayer.cpp
 *
 *  Created on: Aug 18, 2011
 *      Author: laschweinski
 */

#include "SynthFmodAudioPlayer.h"
#include <stdio.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"

#define szMusicSuffix "|"

namespace core {

SynthFmodAudioPlayer* SynthFmodAudioPlayer::sharedPlayer() {
    static SynthFmodAudioPlayer s_SharedPlayer;
    return &s_SharedPlayer;
}

void ERRCHECKWITHEXIT(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//      exit(-1);
    }
}

bool ERRCHECK(FMOD_RESULT result) {
    if (result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return true;
    }
    return false;
}

SynthFmodAudioPlayer::SynthFmodAudioPlayer() :
        pMusic(0), pBGMChannel(0), iSoundChannelCount(0) {
    init();
}

void SynthFmodAudioPlayer::init() {
    //init
    FMOD_RESULT result;
    FMOD::ChannelGroup *masterChannelGroup;

    /*
     Create a System object and initialize.
     */
    result = FMOD::System_Create(&pSystem);
    ERRCHECKWITHEXIT(result);

    result = pSystem->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECKWITHEXIT(result);

    result = pSystem->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECKWITHEXIT(result);

    result = pSystem->createChannelGroup("Channel Group", &pChannelGroup);
    ERRCHECKWITHEXIT(result);

    result = pSystem->getMasterChannelGroup(&masterChannelGroup);
    ERRCHECKWITHEXIT(result);

    result = masterChannelGroup->addGroup(pChannelGroup);
    ERRCHECKWITHEXIT(result);

    mapEffectSound.clear();

}

void SynthFmodAudioPlayer::close() {
    FMOD_RESULT result;
    //BGM
    if (pBGMChannel != NULL) {
        result = pBGMChannel->stop();
        ERRCHECKWITHEXIT(result);
        pBGMChannel = 0;
    }

    if (pMusic != NULL) {
        result = pMusic->release();
        ERRCHECKWITHEXIT(result);
        pMusic = 0;
    }

    result = pChannelGroup->release();
    ERRCHECKWITHEXIT(result);
    sMusicPath.clear();

    result = pSystem->close();
    ERRCHECKWITHEXIT(result);
    result = pSystem->release();
    ERRCHECKWITHEXIT(result);

    init();
}

SynthFmodAudioPlayer::~SynthFmodAudioPlayer() {
    FMOD_RESULT result;
    //BGM
    if (pBGMChannel != NULL) {
        result = pBGMChannel->stop();
        ERRCHECKWITHEXIT(result);
    }

    if (pMusic != NULL) {
        result = pMusic->release();
        ERRCHECKWITHEXIT(result);
    }

    result = pChannelGroup->release();
    ERRCHECKWITHEXIT(result);

    result = pSystem->close();
    ERRCHECKWITHEXIT(result);
    result = pSystem->release();
    ERRCHECKWITHEXIT(result);
}

// BGM
void SynthFmodAudioPlayer::preloadBackgroundMusic(const char* pszFilePath) {
    FMOD_RESULT result;
    pSystem->update();
    string sNewMusicPath = string(pszFilePath) + szMusicSuffix;
    if (pMusic && sNewMusicPath != sMusicPath) {
        //release old
        result = pMusic->release();
        ERRCHECKWITHEXIT(result);

        sMusicPath = sNewMusicPath;

    }

    result = pSystem->createSound(pszFilePath, FMOD_LOOP_NORMAL, 0, &pMusic);
    ERRCHECK(result);
}

void SynthFmodAudioPlayer::playBackgroundMusic(const char* pszFilePath, bool bLoop) {
    pSystem->update();
    if (pMusic == NULL) {
        //did not load it
        //load the new music
        FMOD_RESULT result = pSystem->createSound(pszFilePath, FMOD_LOOP_NORMAL,
                0, &pMusic);
        if (!ERRCHECK(result)) {
            sMusicPath = string(pszFilePath) + szMusicSuffix;
        }

    } else {
        string sNewMusicPath = string(pszFilePath) + szMusicSuffix;
        if (pBGMChannel) {
            pBGMChannel->stop();
            pBGMChannel = 0;
        }

        if (sNewMusicPath != sMusicPath) {

            pMusic->release();
            //load the new music
            FMOD_RESULT result = pSystem->createSound(pszFilePath,
                    FMOD_LOOP_NORMAL, 0, &pMusic);

            if (!ERRCHECK(result)) {
                sMusicPath = sNewMusicPath;
            }
        }

    }

    FMOD_RESULT result = pSystem->playSound(FMOD_CHANNEL_FREE, pMusic, true,
            &pBGMChannel);
    if (!ERRCHECK(result)) {
        pBGMChannel->setLoopCount((bLoop) ? -1 : 0);
        result = pBGMChannel->setPaused(false);
    }
}

void SynthFmodAudioPlayer::stopBackgroundMusic(bool bReleaseData) {
    FMOD_RESULT result;
    pSystem->update();

    if (pBGMChannel == NULL || pMusic == NULL) {
        return;
    }
    if (bReleaseData) {
        result = pBGMChannel->stop();
        ERRCHECKWITHEXIT(result);
        result = pMusic->release();
        ERRCHECKWITHEXIT(result);
        pBGMChannel = 0;
        pMusic = 0;
    } else {
        result = pBGMChannel->stop();
        ERRCHECKWITHEXIT(result);
        pBGMChannel = 0;
    }
    sMusicPath.clear();

}

void SynthFmodAudioPlayer::pauseBackgroundMusic() {
    if (pBGMChannel == NULL) {
        return;
    }
    pSystem->update();
    FMOD_RESULT result = pBGMChannel->setPaused(true);
    ERRCHECKWITHEXIT(result);

}

void SynthFmodAudioPlayer::resumeBackgroundMusic() {
    if (pBGMChannel == NULL) {
        return;
    }
    pSystem->update();
    FMOD_RESULT result = pBGMChannel->setPaused(false);
    ERRCHECKWITHEXIT(result);
}

void SynthFmodAudioPlayer::rewindBackgroundMusic() {
    if (pBGMChannel == NULL) {
        return;
    }
    pSystem->update();
    FMOD_RESULT result = pBGMChannel->setPosition(0, FMOD_TIMEUNIT_MS);
    ERRCHECKWITHEXIT(result);
}

bool SynthFmodAudioPlayer::willPlayBackgroundMusic() {
    pSystem->update();
    return false; //do it according to win
}

bool SynthFmodAudioPlayer::isBackgroundMusicPlaying() {
    bool bPlaying;
    if (pBGMChannel == NULL) {
        return false;
    }
    pSystem->update();
    FMOD_RESULT result = pBGMChannel->isPlaying(&bPlaying);
    ERRCHECKWITHEXIT(result);
    return bPlaying;

}

float SynthFmodAudioPlayer::getBackgroundMusicVolume() {
    float fVolumn;
    if (pBGMChannel == NULL) {
        return 0;
    }
    pSystem->update();
    FMOD_RESULT result = pBGMChannel->getVolume(&fVolumn);
    ERRCHECKWITHEXIT(result);
    return fVolumn;
}

void SynthFmodAudioPlayer::setBackgroundMusicVolume(float volume) {
    if (pBGMChannel == NULL) {
        return;
    }
    pSystem->update();
    FMOD_RESULT result = pBGMChannel->setVolume(volume);
    ERRCHECKWITHEXIT(result);

}
//~BGM

// for sound effects
float SynthFmodAudioPlayer::getEffectsVolume() {
    float fVolumn;
    pSystem->update();
    FMOD_RESULT result = pChannelGroup->getVolume(&fVolumn);
    ERRCHECKWITHEXIT(result);
    return fVolumn;
}

void SynthFmodAudioPlayer::setEffectsVolume(float volume) {
    pSystem->update();
    FMOD_RESULT result = pChannelGroup->setVolume(volume);
    ERRCHECKWITHEXIT(result);

}

unsigned int SynthFmodAudioPlayer::playEffect(const char* pszFilePath, bool bLoop,
                                         float pitch, float pan, float gain) {
    FMOD::Channel* pChannel;
    FMOD::Sound* pSound = NULL;

    do {
        pSystem->update();

        map<string, FMOD::Sound*>::iterator l_it = mapEffectSound.find(
                string(pszFilePath));
        if (l_it == mapEffectSound.end()) {
            //no load it yet
            preloadEffect(pszFilePath);
            l_it = mapEffectSound.find(string(pszFilePath));
        }
        pSound = l_it->second;
        if (pSound==NULL){
            break;
        }

        FMOD_RESULT result = pSystem->playSound(FMOD_CHANNEL_FREE, pSound, true,
                &pChannel);

        if (ERRCHECK(result)) {
            printf("sound effect in %s could not be played", pszFilePath);
            break;
        }

        pChannel->setChannelGroup(pChannelGroup);
        pChannel->setPan(pan);
        float freq = 0;
        pChannel->getFrequency(&freq);
        pChannel->setFrequency(pitch * freq);
        pChannel->setVolume(gain);

        //set its loop
        pChannel->setLoopCount((bLoop) ? -1 : 0);
        result = pChannel->setPaused(false);

        mapEffectSoundChannel[iSoundChannelCount] = pChannel;
        return iSoundChannelCount++;
    } while (0);

    return 0;
}

void SynthFmodAudioPlayer::stopEffect(unsigned int nSoundId) {
    FMOD::Channel* pChannel;
    pSystem->update();

    map<unsigned int, FMOD::Channel*>::iterator l_it =
            mapEffectSoundChannel.find(nSoundId);
    if (l_it == mapEffectSoundChannel.end()) {
        //no play  yet
        return;
    }
    pChannel = l_it->second;
    //stop the channel;
    pChannel->stop();

    //delete from the map;
    mapEffectSoundChannel.erase(nSoundId);
}

void SynthFmodAudioPlayer::pauseEffect(unsigned int uSoundId) {
    FMOD::Channel* pChannel;
    pSystem->update();

    map<unsigned int, FMOD::Channel*>::iterator l_it =
            mapEffectSoundChannel.find(uSoundId);
    if (l_it == mapEffectSoundChannel.end()) {
        //no play  yet
        return;
    }
    pChannel = l_it->second;
    //pause the channel;
    pChannel->setPaused(true);
}

void SynthFmodAudioPlayer::pauseAllEffects() {
    FMOD::Channel* pChannel;
    pSystem->update();

    map<unsigned int, FMOD::Channel*>::iterator l_it =
            mapEffectSoundChannel.begin();

    for (; l_it != mapEffectSoundChannel.end(); l_it++) {
        pChannel = l_it->second;
        //pause the channel;
        pChannel->setPaused(true);
    }
}

void SynthFmodAudioPlayer::resumeEffect(unsigned int uSoundId) {
    FMOD::Channel* pChannel;
    pSystem->update();

    map<unsigned int, FMOD::Channel*>::iterator l_it =
            mapEffectSoundChannel.find(uSoundId);
    if (l_it == mapEffectSoundChannel.end()) {
        //no play  yet
        return;
    }

    pChannel = l_it->second;
    //resume the channel;
    pChannel->setPaused(false);
}

void SynthFmodAudioPlayer::resumeAllEffects() {
    FMOD::Channel* pChannel;
    pSystem->update();

    map<unsigned int, FMOD::Channel*>::iterator l_it =
            mapEffectSoundChannel.begin();

    for (; l_it != mapEffectSoundChannel.end(); l_it++) {
        pChannel = l_it->second;
        //resume the channel;
        pChannel->setPaused(false);
    }
}

void SynthFmodAudioPlayer::stopAllEffects() {
    FMOD::Channel* pChannel;
    pSystem->update();

    map<unsigned int, FMOD::Channel*>::iterator l_it =
            mapEffectSoundChannel.begin();

    for (; l_it != mapEffectSoundChannel.end(); l_it++) {
        pChannel = l_it->second;
        //resume the channel;
        pChannel->stop();
    }

    mapEffectSoundChannel.clear();
}

void SynthFmodAudioPlayer::preloadEffect(const char* pszFilePath) {
    FMOD::Sound* pLoadSound;

    pSystem->update();
    FMOD_RESULT result = pSystem->createSound(pszFilePath, FMOD_LOOP_NORMAL, 0,
            &pLoadSound);
    if (ERRCHECK(result)){
        printf("sound effect in %s could not be preload", pszFilePath);
        return;
    }
    mapEffectSound[string(pszFilePath)] = pLoadSound;
}

void SynthFmodAudioPlayer::unloadEffect(const char* pszFilePath) {
    FMOD::Sound* pSound;
    pSystem->update();

    map<string, FMOD::Sound*>::iterator l_it = mapEffectSound.find(
            string(pszFilePath));
    if (l_it == mapEffectSound.end()) {
        //no load  yet
        return;
    }
    pSound = l_it->second;

    //release the sound;
    pSound->release();

    //delete from the map
    mapEffectSound.erase(string(pszFilePath));
}

//~for sound effects

} /* namespace core */
