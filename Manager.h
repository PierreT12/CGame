#ifndef MANAGER_H
#define  MANAGER_H
#pragma once
#include <windows.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "Score.h"

//We only want a single instance of the manager
class Manager
{

public:
	static Manager* CreateInstance();
	static Manager* GetInstance() { return sInstance; };

	//Initalize the game when start is called
	void initGame(GL_Window* window);


	void init();

	//We need game manager to handle all of this and only allow CGame to if it is suppose to be
	void UpdateFrame(DWORD milliseconds, GL_Window* window);

	void DrawScene(GL_Window* window);

	Score* GetPlayerScore(int player);

	void SetGameOver(bool8_t over);

	void SetGameStarted(bool8_t over);


	bool8_t misGameOver;

	bool8_t GetWinner();

	//Make it it's own stuff later
	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;
	

	bool8_t mWinner;

private:
	static Manager* sInstance;

	

	bool8_t mhasGameStarted;

	Score* playerOneScore;
	Score* playerTwoScore;



};
#endif

