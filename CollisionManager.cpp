#include "CollisionManager.h"
#include "baseTypes.h"
#include "Sprite.h"
#include "Collider.h"
#include "collInfo.h"
#include <windows.h>


CollisionManager* CollisionManager::sInstance = nullptr;

CollisionManager* CollisionManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new CollisionManager();
	}
	return sInstance;
}

CollisionManager* CollisionManager::getInstance()
{
	return sInstance;
}

void CollisionManager::init(GL_Window* window)
{

	mWindow = window;

}

//Checking all of the collision needed
void CollisionManager::update(DWORD deltaTime, MainPlayers* player, MapGen* mapGen)
{
	CheckForGrounded(player, mapGen);
	CheckForPlayerPowerUp(player, mapGen);
	CheckForPlayerDeath(player, mapGen);
	CheckForEnemyDeath(player, mapGen);
}


void CollisionManager::CheckForGrounded(MainPlayers* player, MapGen* mapGen)
{
	//Always checking the last one called in the loop
	for (int i = 0; i < 2; i++)
	{
		if (onCollision(player->getSprite(), mapGen->GetSprite(i)))
		{
			player->SetGrounded(TRUE);
			//Breaking so jump can run properly
			break;
		}
		else
		{
			player->SetGrounded(FALSE);
		}
	}


}

//Check for collisions between the player and the enemies and hazards
void CollisionManager::CheckForPlayerDeath(MainPlayers* player, MapGen* mapGen)
{
	//We have to check for each part of the map
	for (int i = 0; i < 2; i++)
	{
		//Only check if the player is alive and isn't invincilbe
		if (player->misAlive == TRUE && player->misInvi == FALSE)
		{
			//Checking Hazards First
			if (mapGen->GetHazard(i)->getSpriteEnabled() == TRUE)
			{
				//If this is true the player is dead
				if (onCollision(player->getSprite(), mapGen->GetHazard(i)))
				{
					player->misAlive = FALSE;
					player->getScoreBoard()->mIsPlayerDead = TRUE;
					//player->SetDeathAnimation();

				}
			}
			//Then check enemies
			if (mapGen->GetEnemy(i)->getSpriteEnabled() == TRUE)
			{
				//If this is true the player is dead
				if (onCollision(player->getSprite(), mapGen->GetEnemy(i)))
				{
					player->misAlive = FALSE;
					player->getScoreBoard()->mIsPlayerDead = TRUE;
					//player->SetDeathAnimation();

				}
			}
		}
		

	}



}

//Checking the powerup collision
void CollisionManager::CheckForPlayerPowerUp(MainPlayers* player, MapGen* mapGen)
{
	for (int i = 0; i < 2; i++)
	{
		if (mapGen->GetPowerUp(i)->GetPowerType() != PowerType::INVALID_POWER)
		{
			if (onCollision(player->getSprite(), mapGen->GetPowerUp(i)->GetSprite()))
			{
				if (player->GetHolder()->GetPowerUp() == nullptr)
				{
					player->GetHolder()->SetPowerUp(mapGen->GetPowerUp(i), mWindow);
					break;
				}
			}
		}
		
	}



}

//Check for enemy collision with player projectiles
void CollisionManager::CheckForEnemyDeath(MainPlayers* player, MapGen* mapGen)
{
	for (int i = 0; i < 2; i++)
	{
		//Checking Hazards First
		if (mapGen->GetEnemy(i)->getSpriteEnabled() == TRUE)
		{
			if (onCollision(player->getAttack()->getSprite(), mapGen->GetEnemy(i)))
			{
				mapGen->GetEnemy(i)->disableSprite();
				player->getAttack()->SetTimer(0.0f);

			}
		}

		

	}

}

bool8_t CollisionManager::onCollision(Sprite* spriteA, Sprite* spriteB)
{
	// Calculate positions for collider of SpriteA
	Coord2D* positionA = spriteA->getPosition();
	Collider* colliderA = spriteA->getCollider();

	float_t leftA = positionA->x + colliderA->getOffsetX();
	float_t rightA = leftA + colliderA->getWidth();
	float_t bottomA = positionA->y + colliderA->getOffsetY();
	float_t topA = bottomA + colliderA->getHeight();
	// Calculate positions for collider of SpriteB
	Coord2D* positionB = spriteB->getPosition();
	Collider* colliderB = spriteB->getCollider();

	float_t leftB = positionB->x + colliderB->getOffsetX();
	float_t rightB = leftB + colliderB->getWidth();
	float_t bottomB = positionB->y + colliderB->getOffsetY();
	float_t topB = bottomB + colliderB->getHeight();
	// Check for collision
	if (leftA < rightB && rightA > leftB && topA > bottomB && bottomA < topB)
	{
		return TRUE;
	}
	return FALSE;
}

void CollisionManager::shutdown()
{
	
}

