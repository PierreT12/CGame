#ifndef MAIN_PLAY_H
#define MAIN_PLAY_H
#pragma once
#include "baseTypes.h"
#include "Sprite.h"
#include "collInfo.h"
#include "object.h"
#include "field.h"
#include "ShapeDraw.h"
#include "Attack.h"
#include "Score.h"
#include "ItemHolder.h"


//Where Player 1 and 2 are created
class MainPlayers
{

private:
	Sprite* mSprite;
	
	bool8_t mIsGrounded;
	bool8_t mcanFire;
	
	bool8_t misPlayer1;

	

	GL_Window* mWindow;

	Attack * mAttack;
	
	Score* mScore;

	ItemHolder* mHolder;

	Sprite* mBackground;

	//This is our animation counter for walking
	int16_t mCounter;

	int16_t mFrameCounter;

	int16_t mJumpSpeed;

	int16_t mJumpTimer;

	int16_t mJumpCoolDown;

	int16_t mJumpFrameCounter;

	int16_t mPowerUpTimer;

	int16_t mDeathCounter;

	int16_t mDeathFrameCounter;

	float_t SPEED;

	void shoot();

	void setSprite();

	void SetSpriteNumb(int16_t* numb, char* file);

	void UsePowerUp(PowerType type);

public:
	bool8_t misAlive;
	bool8_t misAttack;
	bool8_t misInvi;

	Sprite* getSprite();
	Sprite* GetBackground();

	bool8_t getPlayer();

	GL_Window* getWindow();

	Attack* getAttack();

	Score* getScoreBoard();

	ItemHolder* GetHolder();

	void SetTimer(int16_t time);

	void SetInvi(bool8_t is);

	void SetSpeed(float_t spd);

	float_t GetSpeed();


	void SetGrounded(bool8_t ground);


	void PlayerOneUpdates();

	void PlayerTwoUpdates();

	void JumpUpdates();
	
	void PowerUpUpdates();

	//Handles all animations (Run/Death/Jump)
	void AnimationUpdates();

	void SetDeathAnimation();

	MainPlayers(Sprite* kirbySpirte, bool8_t isAlive, bool8_t isPlayer1, GL_Window* window, Attack* attack, Score* score, ItemHolder* holder, Sprite* background);
	void update(DWORD milliseconds);
	void render();


};




#endif