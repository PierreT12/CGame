#include "StartScreen.h"
#include "openglstuff.h"
#include "AudioManager.h"


StartScreen* StartScreen::sInstance = NULL;


//Returns 
bool8_t StartScreen::GetisGameStart()
{
	return isGameStart;
}

StartScreen* StartScreen::CreateInstance()
{
	sInstance = new StartScreen();
	return sInstance;
}

//Draws to screen
void StartScreen::DrawScene(GL_Window* window)
{

	startOpenGLDrawingStartScreen(mfarBackground,mTitle);
}

//Updates all variables
void StartScreen::UpdateFrame(DWORD milliseconds, GL_Window* window)
{
	mfarBackground->updateSprite(milliseconds);
	mTitle->updateSprite(milliseconds);

	//Checks to see if the space bar has been pressed to start the game
	if (GetKeyState(' ') & 0x8000)
	{
		isGameStart = TRUE;
	}

}
//Initalizes all Sprites and other variables
void StartScreen::init(GL_Window* window)
{
	mfarBackground = new Sprite(-2000.0f, -2000.0f, 4000, 4000, "Sprites\\Start Screen\\Background.png", 0);

	mfarBackground->init(window);

	mTitle = new Sprite(-2000.0f, 0.0f, 4000, 2000, "Sprites\\Start Screen\\Title.png", 0);

	mTitle->init(window);


	isGameStart = FALSE;


}
