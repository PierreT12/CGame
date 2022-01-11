#pragma once
#include "Manager.h"
#include "game.h"
#include "StartScreen.h"
#include "GameOver.h"
#include "openGLStuff.h"
#include "AudioManager.h"
#include "openglframework.h"
#include "random.h"


Manager* Manager::sInstance = NULL;

//Initalizes all the important stuff
BOOL Initialize(GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window, keys, 0.0f, 0.0f, 0.0f);
	AudioManager::createInstance();
	AudioManager::getInstance()->init();
	Manager::CreateInstance();
	Manager::GetInstance()->init();
	Manager::GetInstance()->initGame(window);


	return TRUE;

}

Manager* Manager::CreateInstance()
{
	sInstance = new Manager();
	return sInstance;
}

//Initaailize Screens
void Manager::initGame(GL_Window* window)
{
	//Starting game if player has pressed start
	if (mhasGameStarted == TRUE)
	{
		if (CGame::GetInstance() == NULL)
		{
			CGame::CreateInstance();
		}
		
		CGame::GetInstance()->init(window);
		AudioManager::getInstance()->PlayGame();
	}
	//Create Intro Screen
	else if (misGameOver == FALSE && mhasGameStarted == FALSE)
	{
		if (StartScreen::GetInstance() == NULL)
		{
			StartScreen::CreateInstance();
		}
		
		StartScreen::GetInstance()->init(window);
		AudioManager::getInstance()->PlayStartScreen();
	}
	//Create Game Over Screen
	else if(misGameOver == TRUE)
	{
		if (GameOver::GetInstance() == NULL)
		{
			GameOver::CreateInstance();
		}
		GameOver::GetInstance()->init(window);
	

		playerOneScore = CGame::GetInstance()->GetPlayerOne()->getScoreBoard();
		playerOneScore = CGame::GetInstance()->GetPlayerTwo()->getScoreBoard();
		
	
	}
	
}

//Initialize Managers
void Manager::init()
{
	mhasGameStarted = FALSE;
	misGameOver = FALSE;


}

//Updates Frames
void Manager::UpdateFrame(DWORD milliseconds, GL_Window* window)
{
	keyProcess();
	if (mhasGameStarted == TRUE && misGameOver == FALSE)
	{
		CGame::GetInstance()->UpdateFrame(milliseconds, window);
	}
	else if (misGameOver == FALSE && mhasGameStarted == FALSE)
	{

		StartScreen::GetInstance()->UpdateFrame(milliseconds, window);

		mhasGameStarted = StartScreen::GetInstance()->GetisGameStart();

		if (mhasGameStarted == TRUE)
		{
			Manager::GetInstance()->initGame(window);
		}

	}
	else if (misGameOver == TRUE)
	{

		GameOver::GetInstance()->UpdateFrame(milliseconds, window);

		mhasGameStarted = GameOver::GetInstance()->GetGameRestart();


		if (mhasGameStarted == TRUE)
		{
			misGameOver = FALSE;
			Manager::GetInstance()->initGame(window);

			GameOver::GetInstance()->mGameRestart = FALSE;
		}
	}

}



//Draws the scenes
void Manager::DrawScene(GL_Window* window)
{
	if (mhasGameStarted == TRUE && misGameOver == FALSE)
	{
		CGame::GetInstance()->DrawScene(window);
	}
	else if (misGameOver == FALSE && mhasGameStarted == FALSE)
	{

		StartScreen::GetInstance()->DrawScene(window);
	}
	else if (misGameOver == TRUE)
	{
		initGame(window);
		GameOver::GetInstance()->DrawScene(window);
	}
}

//Setters/Getters
void Manager::SetGameOver(bool8_t over)
{
	misGameOver = over;
}

void Manager::SetGameStarted(bool8_t over)
{
	mhasGameStarted = over;
}

bool8_t Manager::GetWinner()
{
	int16_t playerOneScore = CGame::GetInstance()->GetPlayerOne()->getScoreBoard()->GetActualScore();
	int16_t playerTwoScore = CGame::GetInstance()->GetPlayerTwo()->getScoreBoard()->GetActualScore();
	
	if (playerOneScore > playerTwoScore)
	{
		mWinner = 1;
		return 1;
	}
	//Randomly chooses a winner if they get the same score
	else if (playerOneScore == playerTwoScore)
	{
		return getRangedRandom(0, 1);
	}
	else
	{
		mWinner = 1;
		return 0;
	}


}


Score* Manager::GetPlayerScore(int player)
{
	if (CGame::GetInstance() != NULL)
	{
		if (player == 1)
		{
			return  CGame::GetInstance()->GetPlayerOne()->getScoreBoard();
		}
		else
		{
			return CGame::GetInstance()->GetPlayerTwo()->getScoreBoard();
		}
	}
}