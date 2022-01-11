#ifndef GEN_H
#define GEN_H
#pragma once
#include "baseTypes.h"
#include "Sprite.h"
#include "collInfo.h"
#include "object.h"
#include "field.h"
#include "ShapeDraw.h"





struct Generation
{
	Sprite* mbackground;
	int16_t mplatNumb;
	//Enemies
	//Powerups
	bool8_t mhasEnemies;
	bool8_t mhasPowerUps;
	bool8_t mhasHazard;


	Generation(Sprite* thisSprite, bool8_t hasEnemies, bool8_t hasPowerUps, bool8_t hasHazards)
	{
		mbackground = thisSprite;
		mhasEnemies = hasEnemies;
		mhasPowerUps = hasPowerUps;
		mhasHazard = hasHazards;
	}

};







#endif