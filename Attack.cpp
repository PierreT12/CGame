#include "Attack.h"
/*
* Attacks handels the attacks from player one and player two on the enemies that spawn on the screen
* each player has a different attack avalible that they can use
* the attacks eventually clear from the screen
*/
Attack* Attack::instance = NULL;
Attack::Attack(Sprite* attack, float_t Speed, GL_Window* window, float_t aliveTime)
{
	mSprite = attack; //set the sprite for the attack (player 1 and player 2 have different attacks)

	mBaseSpeed = Speed; //set the orriginal speed for the projectile
	
	mWindow = window;

	mAliveTime = aliveTime; //tracks the time the attack is allive because eventually it will vanish


	SetAttackSpeed(mBaseSpeed);

	
}


void Attack::update(DWORD milliseconds, float_t currentSpeed)
{
	//if the attack is active, 
	if (mSprite->getSpriteEnabled() == TRUE)
	{
		//if you still have time left alive for the projectile
		if (mAliveTime > 0)
		{
			mAliveTime -= 1.0f; //decrease the counter for the time allowed for the pwojectile

			SetAttackSpeed(currentSpeed); // set the attack speed based off of the current speed
			mSprite->updateSprite(milliseconds);
		}
		else
		{
			//otherwise disabel the sprite to nolonger show it on the screen
			mSprite->disableSprite();
		}
	}
	
}


//update the velocity for the attack projectile
void Attack::SetAttackSpeed(float_t Speed)
{

	mSprite->setVelocity(Speed, 0.0f);


}

//returns the attack sprite
Sprite* Attack::getSprite()
{
	return mSprite;
}
//set the timer based off of the initical time passed in
void Attack::SetTimer(float_t time)
{
	mAliveTime = time;
}
