#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SoundSystem.h"

class AudioManager
{
		
public:
	~AudioManager() {};

	static AudioManager* createInstance();
	static AudioManager* getInstance() { return sInstance; }

	void init();
	void update();
	void shutdown();

	// Play sound for firing of bullets
	void playFiringSound();
	// Play sound when enemy plane enters allied area
	void playAirRaidSound();

	void PlayStartScreen();

	void PlayGame();

	void PlayKirbyWin();

	void PlayMetaWin();

private:
	AudioManager() {};

	static AudioManager* sInstance;
	SoundSystem* mSoundSystem;

	Sound fireSound;
	Sound airRaid;

	Sound start;
	Sound run;



	Sound kirbyWin;
	Sound metaWin;
};

#endif