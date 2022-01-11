#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "baseTypes.h"
#include "Sprite.h"
#include "MainPlayers.h"
#include "MapGen.h"
#include "powerUps.h"
#include <windows.h>

class CollisionManager
{

public:
	~CollisionManager() {};

	static CollisionManager* createInstance();
	static CollisionManager* getInstance();

	void init(GL_Window* window);
	void update(DWORD deltaTime, MainPlayers* player, MapGen* mapGen);
	void shutdown();

private:
	CollisionManager() {};

	static CollisionManager* sInstance;
	// Checks if any plane was hit by enemy bullets
	void checkForPlaneShotDown();

	void CheckForGrounded(MainPlayers* player, MapGen* mapGen);

	//Checking Hazards
	void CheckForPlayerDeath(MainPlayers* player, MapGen* mapGen);

	void CheckForPlayerPowerUp(MainPlayers* player, MapGen* mapGen);

	void CheckForEnemyDeath(MainPlayers* player, MapGen* mapGen);

	// Returns true if two sprite's collider's are colliding
	bool8_t onCollision(Sprite*, Sprite*);

	GL_Window* mWindow;
};

#endif