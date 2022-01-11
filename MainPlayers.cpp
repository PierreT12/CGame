#pragma once
#include "MainPlayers.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "game.h"


#define GRAVITY  00.00f




//Constructor for Main Player
MainPlayers::MainPlayers(Sprite* kirbySpirte, bool8_t isAlive, bool8_t isPlayer1, GL_Window* window, Attack* attack, Score* score, ItemHolder* holder, Sprite* background)
{
	mSprite = kirbySpirte;
	misAlive = isAlive;
	misPlayer1 = isPlayer1;
	mWindow = window;

	mBackground = background;

	mAttack = attack;
	
	mScore = score;

	mHolder = holder;
	
	mScore->getSpritePlate()->init(mWindow);

	mHolder->GetHolder()->init(mWindow);


	mBackground->init(window);

	misInvi = FALSE;


	mBackground->setPosition(mSprite->getPosition()->x - 2200, mSprite->getPosition()->y - 1200);

	mJumpSpeed = 0;
	mJumpTimer = -1;
	mJumpCoolDown = 0;

	//MainAnimation Timer
	mCounter = 0;

	mFrameCounter = 0;

	mDeathCounter = -1;
	mDeathFrameCounter = -1;


	mPowerUpTimer = -1;

	//Sweet spot for speed
	SPEED = 1750.0F;
}


//Main update function for the players
void MainPlayers::update(DWORD milliseconds )
{
	if (misAlive == TRUE)
	{
	
		
		if (misPlayer1 == TRUE)
		{

			PlayerOneUpdates();
		}
		else
		{
			PlayerTwoUpdates();
		}



		
		AnimationUpdates();

		JumpUpdates();

		PowerUpUpdates();



		mSprite->updateSprite(milliseconds);

		mAttack->update(milliseconds, (mSprite->getVelocity()->x + 1000));


		mScore->getSpritePlate()->setPosition(mSprite->getPosition()->x - 2100, mSprite->getPosition()->y + 800);
		mScore->getSpritePlate()->updateSprite(milliseconds);

		mHolder->GetHolder()->setPosition(mSprite->getPosition()->x + 1650, mSprite->getPosition()->y + 1040);
		mHolder->update(milliseconds);

		mBackground->setVelocity(mSprite->getVelocity()->x, 0.0f);
		mBackground->updateSprite(milliseconds);


		mFrameCounter++;

		//Speed will randomly go to crazy negative/positve numbers and this is a hotfix
		if (SPEED < -1)
		{
			SPEED = 1750.0;
		}

		if (SPEED > 2500)
		{
			SPEED = 1750.0;
		}
	}
	//Stop it if it's dead
	else
	{
		SPEED = 0;
		mSprite->setVelocity(0.0f, 000.0f);
		mDeathFrameCounter++;
	}

	
}

//All Player 1 Keys and Updates
void MainPlayers::PlayerOneUpdates()
{
	
	if (GetKeyState('W') & 0x8000)
	{
		if (mIsGrounded == TRUE && mJumpCoolDown == 0)
		{
			int tempSpeed = SPEED + 1250;
			mJumpSpeed = 3000.0f;
			mSprite->setVelocity(tempSpeed, mJumpSpeed);
			mJumpTimer = 50;
			mIsGrounded = FALSE;

		}


	}
	else if (GetKeyState('Q') & 0x8000)
	{
		mAttack->getSprite()->init(mWindow);

		mAttack->getSprite()->setPosition(mSprite->getPosition()->x + 300.0, mSprite->getPosition()->y + 50.0);
		mAttack->getSprite()->setVelocity(SPEED, mSprite->getVelocity()->y);

		//Reset timer
		mAttack->SetTimer(300.0f);

	}
	else if (GetKeyState('E') & 0x8000)
	{
		if (mHolder->GetPowerUp() != nullptr)
		{
			UsePowerUp(mHolder->GetPowerUp()->GetPowerType());
			mHolder->ResetPoweUp();
		}
	}
	else
	{
		mSprite->setVelocity(SPEED, mSprite->getVelocity()->y);
	}



}



//All Player 2 Keys and Updates
void MainPlayers::PlayerTwoUpdates()
{
	
	if (GetKeyState('O') & 0x8000)
	{
		if (mIsGrounded == TRUE && mJumpCoolDown == 0)
		{
			int tempSpeed = SPEED + 1250;
			mJumpSpeed = 3000.0f;
			mSprite->setVelocity(tempSpeed, mJumpSpeed);
			mJumpTimer = 50;
			mIsGrounded = FALSE;

		}


	}
	else if (GetKeyState('I') & 0x8000)
	{
		mAttack->getSprite()->init(mWindow);

		mAttack->getSprite()->setPosition(mSprite->getPosition()->x + 300.0, mSprite->getPosition()->y + 50.0);
		mAttack->getSprite()->setVelocity(SPEED, mSprite->getVelocity()->y);

		//Reset timer
		mAttack->SetTimer(300.0f);

	}
	else if (GetKeyState('P') & 0x8000)
	{
		if (mHolder->GetPowerUp() != nullptr)
		{
			UsePowerUp(mHolder->GetPowerUp()->GetPowerType());
			mHolder->ResetPoweUp();
		}
	}
	if (mJumpTimer > 0)
	{
		mSprite->setWidth(325);
		mSprite->setHeight(325);
	}
	else
	{
		mSprite->setWidth(300);
		mSprite->setHeight(300);
	}

}

//All the Jump stuff
void MainPlayers::JumpUpdates()
{
	if (mJumpTimer > 25)
	{
		mJumpTimer -= 1;

		if (mJumpSpeed < 4000.0f)
		{
			mJumpSpeed += 1000.0f;
			mSprite->setVelocity(mSprite->getVelocity()->x, mJumpSpeed);
		}
	}
	if (mJumpTimer <= 25 && mJumpTimer > 0)
	{
		mJumpTimer -= 1;
		mJumpSpeed -= 500.0f;
		mSprite->setVelocity(mSprite->getVelocity()->x, mJumpSpeed);

		if (mJumpTimer == 1)
		{
			mJumpCoolDown = 50;
		}
	}


	if (mIsGrounded == TRUE)
	{
		mSprite->setVelocity(SPEED, 0.0f);
		

	}

	if (mJumpCoolDown > 0)
	{
		mJumpCoolDown -= 1;
	}
}

//All powerup Updates
void MainPlayers::PowerUpUpdates()
{
	if (mPowerUpTimer > 0)
	{
		mPowerUpTimer -= 1;
	}
	if (mPowerUpTimer == 0)
	{
		misInvi = FALSE;
		SPEED = 1750.0f;
		mSprite->setVelocity(SPEED, mSprite->getVelocity()->y);
		mSprite->setWidth(300);
		mSprite->setHeight(300);
		mPowerUpTimer = -1;
	}



}

//All animation updates
void MainPlayers::AnimationUpdates()
{
	//Trying to prevent seizures
	int16_t counterLimit;
	if (misInvi == TRUE)
	{
		counterLimit = 15;
	}
	else if(misAlive = TRUE)
	{
		counterLimit = 7;
	}
	else
	{
		counterLimit = 7;

	}

	if (misAlive == TRUE)
	{
		if (mFrameCounter >= counterLimit)
		{
			setSprite();
			mFrameCounter = 0;
		}
	}
	if (misAlive == FALSE)
	{

			setSprite();

	}

}


//Getters/Setters
void MainPlayers::SetDeathAnimation()
{
	mCounter = -1;
	mDeathCounter = 0;

}


//Render Method
void MainPlayers::render()
{

	switch (misPlayer1)
	{
	case 1:
		mSprite->render();
		mAttack->getSprite()->render();
		break;

	case 0:
		mSprite->render();
		mAttack->getSprite()->render();
		break;

	}
	
}

//Sets the sprite main file path
void MainPlayers::setSprite()
{
	char* mainPath = (char*)malloc(150);

	int16_t maxCount;

	switch (misPlayer1)
	{
	case 1:
		 if (mJumpTimer > 0)
		{
			strcpy(mainPath, "Sprites\\KirbySpriteSheet\\Jump\\Jump");
			if (misInvi == TRUE)
			{
				strcpy(mainPath, "Sprites\\KirbySpriteSheet\\FlashJump\\Jump");
			}
			maxCount = 10;
		}
		else
		{
			strcpy(mainPath, "Sprites\\KirbySpriteSheet\\Run\\Run");
			if (misInvi == TRUE)
			{
				strcpy(mainPath, "Sprites\\KirbySpriteSheet\\FlashRun\\Run");
			}
			maxCount = 8;
		}

		 if (misAlive == FALSE)
		 {
			 strcpy(mainPath, "Sprites\\KirbySpriteSheet\\Death\\Death");
		 }
		
		break;

	case 0:
		if (mJumpTimer > 0)
		{
			strcpy(mainPath, "Sprites\\MetaSpriteSheet\\Jump\\Jump");
			if (misInvi == TRUE)
			{
				strcpy(mainPath, "Sprites\\MetaSpriteSheet\\FlashJump\\Jump");
			}
			maxCount = 9;
		}
		else
		{
			strcpy(mainPath, "Sprites\\MetaSpriteSheet\\Run\\Run");
			if (misInvi == TRUE)
			{
				strcpy(mainPath, "Sprites\\MetaSpriteSheet\\FlashRun\\Run");
			}
			maxCount = 8;
		}
		break;

	}
	

	char filePath[6];

	//Reseting the counter if it has already played the animation
	if (mCounter >= maxCount)
	{
		mCounter = 0;
	}

	if (misAlive == FALSE)
	{
		mCounter = 4;
	}
	
	SetSpriteNumb(&mCounter, filePath);
	strcat(mainPath, filePath);

	mSprite->ChangeSprite(mainPath);

	if (mCounter != -1)
	{
		mCounter++;
	}
	else if(mDeathCounter != -1)
	{
		mDeathCounter++;
	}
}

void MainPlayers::SetSpriteNumb(int16_t* numb, char* file)
{
	file[0] = *numb + '0';
	file[1] = '.';
	file[2] = 'p';
	file[3] = 'n';
	file[4] = 'g';
	file[5] = '\0';
}


void MainPlayers::UsePowerUp(PowerType type)
{

	switch (type)
	{
	case PowerType::SPEED_UP:
		CGame::GetInstance()->SpeedUp(&misPlayer1, &SPEED);
			break;

	case PowerType::SPEED_DOWN:
		CGame::GetInstance()->SlowDown(&misPlayer1, &SPEED);
		break;

	case PowerType::INVINCBLE:
		CGame::GetInstance()->Invincible(&misPlayer1);
		break;

	case PowerType::BIGGER_SIZE:
		CGame::GetInstance()->Bigger(&misPlayer1);
		break;

	default:
		break;
	}
}




Sprite* MainPlayers::getSprite()
{
	return mSprite;
}


Sprite* MainPlayers::GetBackground()
{
	return mBackground;
}


GL_Window* MainPlayers::getWindow()
{
	return mWindow;
}

Attack* MainPlayers::getAttack()
{
	return mAttack;
}

Score* MainPlayers::getScoreBoard()
{
	return mScore;
}

ItemHolder* MainPlayers::GetHolder()
{
	return mHolder;
}

void MainPlayers::SetTimer(int16_t time)
{
	mPowerUpTimer = time;
}

void MainPlayers::SetInvi(bool8_t is)
{
	misInvi = is;

}

void MainPlayers::SetSpeed(float_t spd)
{

	SPEED = spd;
}

float_t MainPlayers::GetSpeed()
{
	return SPEED;
}


void MainPlayers::SetGrounded(bool8_t ground)
{
	mIsGrounded = ground;
}




