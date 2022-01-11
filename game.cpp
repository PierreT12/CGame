//Gourmet Race: Infinite: CGame File
//	This File:
//		Updates and Controls everything in the main game loop
//		Handles the application of power ups to the players

#define GAME_CPP
#define PLAYER_LEVEL 2
#define TILE_NUMBERS 3
#define TIMER 300

#define SPEED_CHANGE 600
#define SPEED_LIMIT 1000 

#define SCORE_WIDHT 1500
#define SCORE_HEIGHT 700

#define SPRITE_LAYER 0


#pragma once
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "field.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "Sprite.h"
#include "Collider.h"
#include "MainPlayers.h"									//Player Character Class
#include "Attack.h"											//Attack Class
#include "Score.h"											//Score Class
#include "ItemHolder.h"
#include "CollisionManager.h"
#include "AudioManager.h"
#include "Manager.h"



// Declarations
const char8_t CGame::mGameTitle[] = "Gourmet Race: Infinite";
CGame* CGame::sInstance = NULL;




//This Initilzes everything needed for the main game
//It's all split up for readability and for ease of editing
void CGame::init(GL_Window* window)
{

	//Player Attacks Created
	kirbyAttack = new Attack(new Sprite(-SPEED_LIMIT, SCORE_HEIGHT, 100, 200, "Sprites\\Attacks\\KirbyAttack.png", SPRITE_LAYER), SCORE_WIDHT, window, SPEED_CHANGE);
	metaAttack = new Attack(new Sprite(-SPEED_LIMIT, SCORE_HEIGHT, 200, 200, "Sprites\\Attacks\\MetaKnightAttack.png", SPRITE_LAYER), SCORE_WIDHT, window, SPEED_CHANGE);


	//Creating Colliders for their attacks
	kirbyAttack->getSprite()->createCollider(0, 0, 200, 200, ATTACK, kirbyAttack->getSprite());
	metaAttack->getSprite()->createCollider(0, 0, 200, 200, ATTACK, metaAttack->getSprite());

	

	//Disable these sprites on startup
	kirbyAttack->getSprite()->disableSprite();
	metaAttack->getSprite()->disableSprite();
	
	//Player Scores created
	kirbyScore = new Score(new Sprite(-SPEED_LIMIT, SCORE_HEIGHT, SCORE_WIDHT, SCORE_HEIGHT, "Sprites\\Score\\ScoreKirby.png", SPRITE_LAYER), 1);
	metaScore = new Score(new Sprite(-SPEED_LIMIT, SCORE_HEIGHT, SCORE_WIDHT, SCORE_HEIGHT, "Sprites\\Score\\ScoreMetaKnight.png", SPRITE_LAYER), 0);
	
	//Player Item Holders created
	kirbyHolder = new ItemHolder(new Sprite(-SPEED_LIMIT, SCORE_HEIGHT, 400, 400, "Sprites\\Items\\ItemHolder.png", SPRITE_LAYER));
	metaHolder = new ItemHolder(new Sprite(-SPEED_LIMIT, SCORE_HEIGHT, 400, 400, "Sprites\\Items\\ItemHolder.png", SPRITE_LAYER));

	//Player Character Sprite
	playerOne = new MainPlayers(new Sprite(-SPEED_LIMIT, -1200, 300, 300, "KirbyTest.png", SPRITE_LAYER), 1 ,1, window,kirbyAttack, kirbyScore, kirbyHolder, new Sprite(-SPEED_LIMIT, -SCORE_HEIGHT, 5000, 5000, "Sprites\\\Background.png", SPRITE_LAYER));
	playerTwo = new MainPlayers(new Sprite(-SPEED_LIMIT, -1200, 300, 300, "MetaTest.png", SPRITE_LAYER), 1, 0, window, metaAttack, metaScore, metaHolder, new Sprite(-SPEED_LIMIT, -SCORE_HEIGHT, 5000, 5000,  "Sprites\\Background.png", SPRITE_LAYER));

	//Creating Map Generation for each player
	playerOneMap = new MapGen();
	playerTwoMap = new MapGen();
	
	//Initalizing  all created sprites
	
	//Attack Sprites
	kirbyAttack->getSprite()->init(window);
	metaAttack->getSprite()->init(window);

	//This is to prevent them from spawning in at the top
	kirbyAttack->getSprite()->disableSprite();
	metaAttack->getSprite()->disableSprite();

	//Player Sprites
	playerOne->getSprite()->init(window);
	playerTwo->getSprite()->init(window);

	//Score Board Sprites
	playerOne->getScoreBoard()->init(window);
	playerTwo->getScoreBoard()->init(window);

	//Item Holder Sprites
	playerOne->GetHolder()->GetHolder()->init(window);
	playerTwo->GetHolder()->GetHolder()->init(window);

	//Initalizing Maps
	playerOneMap->init(window);
	playerTwoMap->init(window);

	//Creating Player Colliders
	playerOne->getSprite()->createCollider(0, 0, playerOne->getSprite()->getWidth(), playerOne->getSprite()->getHeight(), KIRBY, playerOne->getSprite());
	playerTwo->getSprite()->createCollider(0, 0, playerTwo->getSprite()->getWidth(), playerTwo->getSprite()->getHeight(), META_KNIGHT, playerTwo->getSprite());


	//Creating the collider Manager
	CollisionManager::createInstance();
	
	//Initalizing it
	CollisionManager::getInstance()->init(window);




}

//Updates happening each frame
void CGame::UpdateFrame(DWORD milliseconds, GL_Window* window)
{
	//Updating the Maps
	playerOneMap->update(milliseconds, playerOne);
	playerTwoMap->update(milliseconds, playerTwo);

	//Updating the players
	playerOne->update(milliseconds);
	playerTwo->update(milliseconds);

	//Updating player collision
	CollisionManager::getInstance()->update(milliseconds,playerOne, playerOneMap);
	CollisionManager::getInstance()->update(milliseconds,playerTwo, playerTwoMap);

	//Updating ScoreBoards
	playerOne->getScoreBoard()->update(milliseconds);
	playerTwo->getScoreBoard()->update(milliseconds);

	//Checking to see if both players died
	if (playerOne->misAlive == FALSE && playerTwo->misAlive == FALSE)
	{
		//If so, Game Over!!
		Manager::GetInstance()->SetGameOver(TRUE);
		Manager::GetInstance()->SetGameStarted(FALSE);
	}

}

void CGame::DrawScene(GL_Window* window)
{
	//All rendering is run through this due to the "split screens"/ 2 viewports
	startOpenGLDrawing(playerOne, playerTwo, window, playerOneMap, playerTwoMap);

}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{


	
}

//Slows down the player that uses this item
void CGame::SlowDown(bool8_t* ourPlayer, float_t* speed)
{
	//Player 1
	if (*ourPlayer == 1)
	{
		//Checking to see if the player can be slowed down more
		if (playerOne->getSprite()->getVelocity()->x >= (*speed - 1000 ))
		{
			//If so, slow it down, and set a timer
			playerOne->SetSpeed(1000);
			playerOne->SetTimer(TIMER);
		}
		
	}
	//Player 2
	else
	{
		//Checking to see if the player can be slowed down more
		if (playerTwo->getSprite()->getVelocity()->x >= (*speed - 1000))
		{
			//If so, slow it down, and set a timer
			playerTwo->SetSpeed(playerTwo->getSprite()->getVelocity()->x - 1000);
			playerTwo->SetTimer(TIMER);
		}
		
	}

}

//Speeds the opposing player up
void CGame::SpeedUp(bool8_t* ourPlayer, float_t* speed)
{
	//If Player 1 used the item
	if (*ourPlayer == 1)
	{
		// Checking to see if the player can be sped up more
		if (playerTwo->getSprite()->getVelocity()->x <= (playerTwo->GetSpeed() + SPEED_LIMIT ))
		{
			//If so, speed it up and set a timer
			playerTwo->SetSpeed(playerTwo->getSprite()->getVelocity()->x + SPEED_CHANGE);
			playerTwo->SetTimer(TIMER);
		}
		
	}
	//If Player 2 used the item
	else
	{
		// Checking to see if the player can be sped up more
		if (playerOne->getSprite()->getVelocity()->x <= (playerOne->GetSpeed() + SPEED_LIMIT))
		{
			//If so, speed it up and set a timer
			playerOne->SetSpeed(playerOne->getSprite()->getVelocity()->x + SPEED_CHANGE);
			playerOne->SetTimer(TIMER);
		}

		
	}

}

//Will make the player who used it Invincible for a short time
void CGame::Invincible(bool8_t* ourPlayer)
{
	//Player One
	if (*ourPlayer == 1)
	{
		//Makes Invincible and sets timer
		playerOne->SetInvi(TRUE);
		playerOne->SetTimer(TIMER);
	}
	//Player Two
	else
	{
		//Makes Invincible and sets timer
		playerTwo->SetInvi(TRUE);
		playerTwo->SetTimer(TIMER);
	}

}

//Makes the opposing player bigger
void CGame::Bigger(bool8_t* ourPlayer)
{
	//Player One
	if (*ourPlayer == 1)
	{
		//Makes other player bigger and sets timer
		playerTwo->getSprite()->setWidth(SPEED_CHANGE);
		playerTwo->getSprite()->setHeight(SPEED_CHANGE);
		playerTwo->SetTimer(TIMER);

	}
	//Player Two
	else
	{
		// Makes other player bigger and sets timer
		playerOne->getSprite()->setWidth(SPEED_CHANGE);
		playerOne->getSprite()->setHeight(SPEED_CHANGE);
		playerOne->SetTimer(TIMER);
	}

}

//Deleting all of our game objects to prevent memory leak
void CGame::DestroyGame(void)
{
	delete playerOne;
	delete playerTwo;
	delete playerOneMap;
	delete playerTwoMap;
	delete kirbyAttack;
	delete metaAttack;
	//delete kirbyScore;
	//delete metaScore;

	delete kirbyHolder;
	delete metaHolder;

}