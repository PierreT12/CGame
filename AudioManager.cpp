//Audio Manager
// This File:
//	Handles all audio stuff and is a singleton
#include "AudioManager.h"
#include "baseTypes.h"
#include "SoundSystem.h"
#include <windows.h>


AudioManager* AudioManager::sInstance = NULL;

//Creating instance
AudioManager* AudioManager::createInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

//Initalizing the Sound System
void AudioManager::init()
{
	mSoundSystem = new SoundSystem();

	//mSoundSystem->createSound(&metaWin, "Sounds\\Music\\MetaWin.mp3");
	
}

//Update
void AudioManager::update()
{

}

//Shutdown
void AudioManager::shutdown()
{
}


//Plays the Start Screen Music
void AudioManager::PlayStartScreen()
{
	//Get audio file and plays it
	mSoundSystem->createSound(&start, "Sounds\\Music\\StartScreen.mp3");
	mSoundSystem->playSound(start, TRUE);
}

//Play game audio (Gourmet Race Theme)
void AudioManager::PlayGame()
{
	//Clears the last audio file
	mSoundSystem->releaseSound(start);
	//Loads in new audio file and plays it
	mSoundSystem->createSound(&run, "Sounds\\Music\\Race.mp3");
	mSoundSystem->playSound(run, TRUE);
}

//Clears last audio file because I couldn't get this working in time
void AudioManager::PlayKirbyWin()
{
	mSoundSystem->releaseSound(run);

	
}

//Clears last audio file because I couldn't get this working in time
void AudioManager::PlayMetaWin()
{
	mSoundSystem->releaseSound(run);

}
