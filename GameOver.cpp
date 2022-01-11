#include "GameOver.h"
#include "openglstuff.h"
#include "Manager.h"
#include "AudioManager.h"
GameOver* GameOver::sInstance = NULL;



bool8_t GameOver::GetGameRestart()
{
	return mGameRestart;
}

GameOver* GameOver::CreateInstance()
{
	sInstance = new GameOver();
	return sInstance;
}


void GameOver::DrawScene(GL_Window* window)
{
	startOpenGLDrawingGameOverScreen(mfarBackground, Manager::GetInstance()->GetPlayerScore(1), Manager::GetInstance()->GetPlayerScore(0), mWinnerSprite);
}

void GameOver::UpdateFrame(DWORD milliseconds, GL_Window* window)
{
	mfarBackground->updateSprite(milliseconds);
	
	Manager::GetInstance()->GetPlayerScore(1)->update(milliseconds);
	Manager::GetInstance()->GetPlayerScore(0)->update(milliseconds);

	if (GetKeyState('R') & 0x8000)
	{
		mGameRestart = TRUE;
		
	}

	mWinnerSprite->updateSprite(milliseconds);
}

void GameOver::init(GL_Window* window)
{
	mfarBackground = new Sprite(-2000.0f, -2000.0f, 4000, 4000, "Sprites\\GameOver\\GameOver.png", 0);

	mfarBackground->init(window);


	mWinner = Manager::GetInstance()->GetWinner();
	

	mWinnerSprite = new Sprite(-150, -750, 300, 300, "KirbyTest.png", 0);

	mWinnerSprite->init(window);

	if (mWinner == TRUE)
	{
		AudioManager::getInstance()->PlayKirbyWin();
		mWinnerSprite->ChangeSprite("Sprites\\KirbySpriteSheet\\Win\\Win6.png");
	}
	else if (mWinner == FALSE)
	{
		AudioManager::getInstance()->PlayMetaWin();
		mWinnerSprite->ChangeSprite("Sprites\\MetaSpriteSheet\\Win\\Win4.png");
		mWinnerSprite->setWidth(500);
		mWinnerSprite->setHeight(500);
	}


	mGameRestart = FALSE;

}