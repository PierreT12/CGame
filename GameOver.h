#ifndef GAME_OVER_H
#define GAME_OVER_H
#pragma once
#include "openglframework.h"
#include "baseTypes.h"
#include "Sprite.h"
class GameOver
{
public:

	bool8_t GetGameRestart();
	static GameOver* CreateInstance();
	static GameOver* GetInstance() { return sInstance; };
	void DrawScene(GL_Window* window);
	void UpdateFrame(DWORD milliseconds, GL_Window* window);

	void init(GL_Window* window);
	void shutdown();

	bool8_t mGameRestart;
	bool8_t mWinner;

private:
	static GameOver* sInstance;
	GameOver() {};


	Sprite* mfarBackground;
	
	Sprite* mWinnerSprite;
	

	


};
#endif

