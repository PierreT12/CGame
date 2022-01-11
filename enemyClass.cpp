#include "enemyClass.h"

#include "baseTypes.h"
#include "Sprite.h"
#include "MainPlayers.h"
#include "Attack.h"

#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "openglframework.h"	
#include "SOIL.h"
/*
* EnemiesClasss is used to handel the enemies that are spawned on the screen durring the game. It also handels their run cycles as the move across the screen by choosing and setting the appropriate sprite in the cycle.
*/
enemyClass::enemyClass(Sprite* sprite, bool8_t isAlive, GL_Window* window)
{


	mSprite = sprite;
	misAlive = isAlive;
	
	mWindow = window;

	mWalkTimer = 0; //used to check if the sprite has reached the edge of the screen

	mSpeed = 500.0f; //set the original speed of the ememy

	mFrameCounter = 0; //used to decude when to change the sprite (each image remains for 7 frames)
	
	mWalkCounter = 1; //used to choose which sprite in walk cycle to display
}




void enemyClass::render()
{


}

/*
* update the enemy size by first checking if you have reached the edge of the screen, and adjusting the correct values if necessary, 
* next, updateing the frame counter to controle when the sprite changes and then setting and incrementing the appropriate  values
*/
void enemyClass::update(DWORD milliseconds, GL_Window* window)
{
	//if you have reached the edge of the screen, negate the speed and reset the walk timer
	if (mWalkTimer >= 400)
	{
		mSpeed = -mSpeed;
		mWalkTimer = 0;
		
	}

	if (mSprite->getVelocity()->x != 0.0f)
	{
		//Controls when the sprite itself is changed
		if (mFrameCounter >= 7)
		{
			setSprite();
			mFrameCounter = 0;
		}
	}


	mWalkTimer++; //increase the walk timer
	mSprite->setVelocity(mSpeed, 0.0f); //set the speed of the sprite
	mSprite->updateSprite(milliseconds); 

	mFrameCounter++; //increase frame counter
}

void enemyClass::init()
{




}

/*
* returns a pointer to the current sprite
*/
Sprite* enemyClass::GetSprite()
{
	return mSprite;
}

/*
* set sprite sets the enemy sprite based off of the drirection of the sprite's movment and then calls SetSpriteNumb to fill in the rest
*/
void enemyClass::setSprite()
{
	char* mainPath = (char*)malloc(150);

	// depending on the direction the sprite is moving, the first part of the path to the sprite is set
	if (mSprite->getVelocity()->x > 0.0f)
	{
		strcpy(mainPath, "Sprites\\WaddleDoo\\Run\\Run");
	}
	else
	{
		strcpy(mainPath, "Sprites\\WaddleDoo\\FlipRun\\Run");
	}
	

	char filePath[6]; //a string used to hold the rest of the path

	//Reseting the counter if it has already played the animation
	if (mWalkCounter >= 10)
	{
		mWalkCounter = 1;
	}

	SetSpriteNumb(&mWalkCounter, filePath); // call set sprite num to fill in the rest of the path name based off of the walk counter
	strcat(mainPath, filePath); //copy the path to the main path

	mSprite->ChangeSprite(mainPath); //change the sprite to the new sprite found above

	mWalkCounter++; //increase walk number for next cycle
}

/*
* SetSpriteNumb sets the correct file path ending for the imamge in the run cycle needed for the sprite
* in the folder, the pngs are run1, run2, ext so by setting the file path this way, we are able to loop through the run cycle
*/
void enemyClass::SetSpriteNumb(int16_t* numb, char* file)
{
	file[0] = *numb + '0';
	file[1] = '.';
	file[2] = 'p';
	file[3] = 'n';
	file[4] = 'g';
	file[5] = '\0';
}