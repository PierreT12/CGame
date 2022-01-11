#pragma once
#include "Generation.h"
#include "MainPlayers.h"
#include "enemyClass.h"
#include "powerUps.h"
#ifndef MAP_GEN
#define MAP_GEN
class MapGen
{
public:
	
	~MapGen() {};
	MapGen() {};

	void init(GL_Window* window);
	
	void update(DWORD milliseconds, MainPlayers* player);
	
	void render(Sprite* player);

	Sprite* GetSprite(int sprite);
	Sprite* GetHazard(int sprite);
	powerUps* GetPowerUp(int sprite);

	Sprite* GetEnemy(int sprite);



private:
	Generation** genPtrs;


	Sprite** mBackground;

	Sprite** mHazards;
	
	enemyClass** mEnemies;

	powerUps** mPowerUps;

	
};
#endif

