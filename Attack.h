#ifndef ATTACK_H
#define  ATTACK_H
#pragma once
#include "baseTypes.h"
#include "Sprite.h"
#include "collInfo.h"
#include "object.h"
#include "field.h"
#include "ShapeDraw.h"

/*
* Headder file for Attack which handels the attacks from the two players against the spawned NPC enemies
*/
class Attack
{

public:

	Attack(Sprite* attack, float_t Speed, GL_Window* window, float_t aliveTime);

	/*Attack* GetInstance(){ return instance; }
	Attack* SetInstance();*/
	void SetAttackSpeed(float_t Speed);

	Sprite* getSprite();

	void update(DWORD milliseconds, float_t currentSpeed);

	void SetTimer(float_t time);


private:

	float_t mBaseSpeed;	//orriginal speed for the attack
	Sprite* mSprite; //sprite (depending on the player shooting)
	GL_Window* mWindow;
	float_t mAliveTime; //time the attack is alive
	static Attack* instance;


};
#endif

