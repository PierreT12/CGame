#ifndef START_SCREEN_H
#define START_SCREEN_H
#pragma once
#include "openglframework.h"
#include "baseTypes.h"
#include "Sprite.h"
class StartScreen
{

public:

	bool8_t GetisGameStart();
	static StartScreen* CreateInstance();
	static StartScreen* GetInstance() { return sInstance; };
	void DrawScene(GL_Window* window);
	void UpdateFrame(DWORD milliseconds, GL_Window* window);

	void init(GL_Window* window);
	void shutdown();

private:
	static StartScreen* sInstance;
	StartScreen() {};


	Sprite* mfarBackground;
	Sprite* mTitle;
	Sprite* mCursor;

	bool8_t isGameStart;


};
#endif

