#ifndef ENEMY_H
#define  ENEMY_H
#pragma once
/*
* EnemiesClasss is used to handel the enemies that are spawned on the screen durring the game the game
*/
//includes:
#include "baseTypes.h"
#include "Sprite.h"
#include "openglframework.h"			// Header File For The NeHeGL Basecode


class enemyClass
{
public:
	Sprite* mSprite;

	bool8_t mIsGrounded;	//true if the sprite is grounded

	GL_Window* mWindow;


	int16_t mWalkTimer;		//used to check if the sprite has reached the edge of the screen

	bool8_t misAlive;		//indecates if the enemy is alive

	float_t mSpeed;

	int16_t mFrameCounter;		//used to decude when to change the sprite (each image remains for 7 frames)

	int16_t mWalkCounter;		//used to choose which sprite in walk cycle to display
	


public:
	
	enemyClass(Sprite* mSprite, bool8_t isAlive, GL_Window* window);
	//Initialize member functions 
	void render();
	void update(DWORD milliseconds, GL_Window* window);

	void init();

	Sprite* GetSprite(); //returns the ememy sprite pointer

	void setSprite(); //sets the emeny sprite

	void SetSpriteNumb(int16_t* numb, char* file); //used to find the correnct png for a sprite based off its number


};
#endif

