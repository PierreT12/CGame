#ifndef SCORE_H
#define  SCORE_H
#pragma once
#include "baseTypes.h"
#include "Sprite.h"
#include "collInfo.h"
#include "object.h"
#include "ShapeDraw.h"
class Score
{

private:

	//This is going to store the file names of all of the numbers for the list
	char8_t** mnumbs;
	int16_t mactualScore;
	int16_t mlastScore;
	
	//Store the 1000, 100, 10, 1 places on screen properly
	Sprite** mplaces;

	Sprite* mNamePlate;

	float_t mTimer;

	bool8_t mPlayer;


public:

	Score(Sprite* namePlate, bool8_t player);

	void init(GL_Window* window);

	void AddtoScore(int16_t numbToAdd);

	void update(DWORD milliseconds);

	void render();

	void setScoreValues();

	void SetSpriteNumb(int* numb, char* file);

	Sprite* getSpritePlate();

	int16_t GetActualScore();

	bool8_t mIsPlayerDead;

};
#endif

