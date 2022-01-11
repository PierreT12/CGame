#include "powerUps.h"
#include "baseTypes.h"
#include "Attack.h"
#include "Sprite.h"
#include "gameObject.h"
#include "game.h"
/*
* Power Ups handels the four different power ups that the player has access to throughout the game:
* Increase other player's speed, make other player bigger, decrease own speed, and make yourself invincible
* based on the types of power up, the correct sprite is chosen and displayed in the top left corener allowing the player to choose to use it when they wish. 
*/


powerUps::powerUps(Sprite* sprite, PowerType type)
{
	mSprite = sprite;	//appropriate sprite for the power ups

	mType = type;	//the type of power up (make bigger, make other player faster, make self slower, make self invincible)

	//Make this variable depending on the type of powerup
	mPowerTimer = 100;

}

//update the powerups based off  of the time, each poewr up is only used for a certain ammount of time
void powerUps::update(DWORD milliseconds)
{

	if (mPowerTimer <= 0)
	{
		//We reset it whatever it changed
	}

	mSprite->updateSprite(milliseconds);

}

//render the sprite image
void powerUps::render()
{
	mSprite->render();

}

//returns the sprite for the powerup
Sprite* powerUps::GetSprite()
{
	return mSprite;
}

//returns the type of power ups
PowerType powerUps::GetPowerType()
{
	return mType;
}

//based on the type of powerup, SetPowerTypeManual sets the sprite based off of a ceratain power type passed in
void powerUps::SetPowerTypeManual(PowerType type)
{

	switch (type)
	{
	case PowerType::SPEED_UP:
		mType = PowerType::SPEED_UP;
		mSprite->ChangeSprite("Sprites\\Items\\SpeedUp.png");
		break;

	case PowerType::SPEED_DOWN:
		mType = PowerType::SPEED_DOWN;
		mSprite->ChangeSprite("Sprites\\Items\\SlowDown.png");
		break;

	case PowerType::INVINCBLE:
		mType = PowerType::INVINCBLE;
		mSprite->ChangeSprite("Sprites\\Items\\Invinc.png");
		break;

	case PowerType::BIGGER_SIZE:
		mType = PowerType::BIGGER_SIZE;
		mSprite->ChangeSprite("Sprites\\Items\\Bigger.png");
		break;

	default:
		break;
	}
}


//based on the type of powerup, SetPowerTypeManual sets the sprite bassed off of a random number generation in MapGen
void powerUps::SetPowerType(int type)
{
	switch (type)
	{
	case 0:
		mType = PowerType::SPEED_UP;
		mSprite->ChangeSprite("Sprites\\Items\\SpeedUp.png");
		break;

	case 1:
		mType = PowerType::SPEED_DOWN;
		mSprite->ChangeSprite("Sprites\\Items\\SlowDown.png");
		break;

	case 2:
		mType = PowerType::INVINCBLE;
		mSprite->ChangeSprite("Sprites\\Items\\Invinc.png");
		break;

	case 3:
		mType = PowerType::BIGGER_SIZE;
		mSprite->ChangeSprite("Sprites\\Items\\Bigger.png");
		break;

	default:
		break;
	}

}

