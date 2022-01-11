#ifndef POWERUPS_H
#define  POWERUPS_H
#pragma once
#include "baseTypes.h"
#include "Sprite.h"

/*
* header file for power ups which handels the 4 types of powerups avalible to the player throughout the game. 
*/
typedef enum PowerType
{
	INVALID_POWER,
	
	//4 types of powerups
	SPEED_UP,  //increae speed of ther player
	SPEED_DOWN, //decrease your own speed
	INVINCBLE, //make yourself invincible
	BIGGER_SIZE //make the other player bigger

};




class powerUps
{
private:

	Sprite* mSprite; //pointer to the sprite for the powerup
	PowerType mType; //type of poewrup


	int16_t mPowerTimer; //time that powerup is effective

public:
	

	powerUps(Sprite* sprite, PowerType type);

	//Initialize member functions 
	void update(DWORD milliseconds);
	void render();

	Sprite* GetSprite();

	PowerType GetPowerType();

	void SetPowerTypeManual(PowerType type);

	void SetPowerType(int type);



};
#endif
