#include "MapGen.h"
#include "random.h"
#include "Collider.h"
#define MAP_NUMBERS 2
#define SPRITE_WIDTH 4500
#define SPRITE_HEIGHT 4000


void MapGen::init(GL_Window* window)
{
	//Setting aside memeory for each of these objects
	//Each Platform that will be used
	genPtrs = (Generation**)malloc(MAP_NUMBERS * sizeof(Generation*));
	
	mBackground = (Sprite**)malloc(MAP_NUMBERS * sizeof(Sprite*));

	mHazards = (Sprite**)malloc(MAP_NUMBERS * sizeof(Sprite*));

	mEnemies = (enemyClass**)malloc((MAP_NUMBERS * sizeof(enemyClass*)));

	mPowerUps = (powerUps**)malloc((MAP_NUMBERS * sizeof(powerUps*)));
	

	//Generation
	//Parts of the map the spawn one right after the other
	genPtrs[0] = new Generation(new Sprite(-3100.0f, -1200.0f, SPRITE_WIDTH, 100.0f,"Sprites\\Ground.png", 0),0,0,0);
	genPtrs[1] = new Generation(new Sprite(genPtrs[0]->mbackground->getWidth() + genPtrs[0]->mbackground->getPosition()->x, -1200.0f, SPRITE_WIDTH, 100.0f, "Sprites\\Ground.png", 0), 0, 0, 0);
	


	//Background
	mBackground[0] = new Sprite(genPtrs[0]->mbackground->getPosition()->x, genPtrs[0]->mbackground->getPosition()->y - 1800.0f, SPRITE_WIDTH, SPRITE_HEIGHT, "Sprites\\Floor\\Plain.png", 0);
	mBackground[1] = new Sprite(genPtrs[1]->mbackground->getPosition()->x, genPtrs[1]->mbackground->getPosition()->y - 1800.0f, SPRITE_WIDTH, SPRITE_HEIGHT, "Sprites\\Floor\\Plain.png", 0);

	
	//Enemy Creation
	mEnemies[0] = new enemyClass(new Sprite(0, genPtrs[0]->mbackground->getPosition()->y, 300, 300, "MetaTest.png", 0), 1, window);
	mEnemies[1] = new enemyClass(new Sprite(0, genPtrs[0]->mbackground->getPosition()->y, 300, 300, "MetaTest.png", 0), 1, window);
	

	//Hazards Creation
	mHazards[0] = new Sprite(0, genPtrs[0]->mbackground->getPosition()->y, 300, 300, "Sprites\\Hazard\\Hazard.png", 0);
	mHazards[1] = new Sprite(0, genPtrs[0]->mbackground->getPosition()->y, 300, 300, "Sprites\\Hazard\\Hazard.png", 0);
	

	//PowerUps Creation
	mPowerUps[0] = new powerUps(new Sprite(0, genPtrs[0]->mbackground->getPosition()->y, 300, 300, "MetaTest.png", 0), PowerType::INVALID_POWER);
	mPowerUps[1] = new powerUps(new Sprite(0, genPtrs[0]->mbackground->getPosition()->y, 300, 300, "MetaTest.png", 0), PowerType::INVALID_POWER);
	



	//Initalizes every sprite that will be used in this and Creating their colliders
	for (int i = 0; i < MAP_NUMBERS; i++)
	{
		genPtrs[i]->mbackground->createCollider(0, 0, genPtrs[i]->mbackground->getWidth(), genPtrs[i]->mbackground->getHeight(), FLOOR, genPtrs[i]->mbackground);
		genPtrs[i]->mbackground->init(window);


		mBackground[i]->init(window);



		mEnemies[i]->GetSprite()->createCollider(130, 0, 200, 200, ColliderTag::ENEMY, mEnemies[i]->GetSprite());
		mEnemies[i]->GetSprite()->init(window);


		mHazards[i]->createCollider(130, 0, 300, 300, ColliderTag::HAZARD, mHazards[i]);
		mHazards[i]->init(window);
		


		mPowerUps[i]->GetSprite()->createCollider(0, 0, 300, 300, ColliderTag::POWERUP, mPowerUps[i]->GetSprite());
		mPowerUps[i]->GetSprite()->init(window);

		//Sprites that need to be disabled at initalization
		mEnemies[i]->GetSprite()->disableSprite();
		mHazards[i]->disableSprite();
		mPowerUps[i]->GetSprite()->disableSprite();
	}
	

}

//Updates that happen each frame
void MapGen::update(DWORD milliseconds, MainPlayers* player)
{
	float_t shifted;
	int enemySpawn;
	int hazardSpawn;
	int powerUpSpawn;

	//This has to happen for every platform in the Map (2)
	for (int i = 0; i < MAP_NUMBERS; i++)
	{

		genPtrs[i]->mbackground->updateSprite(milliseconds);

		mBackground[i]->updateSprite(milliseconds);

		
		//Checks the sprites position
		if (player->getSprite()->getPosition()->x > ((genPtrs[i]->mbackground->getPosition()->x + genPtrs[i]->mbackground->getWidth()) + 2000))
		{
			//Generates the next Generation piece
			int random = getRangedRandom(0, (MAP_NUMBERS - 1));
			if ((random + 1) == (i + 1))
			{
				random = random + 2;

				if (random > MAP_NUMBERS - 1)
				{
					random = random - 1;
				}
			}

			//Where the next generation piece will be positioned
			shifted = genPtrs[random]->mbackground->getPosition()->x + genPtrs[random]->mbackground->getWidth();

			//Shfits the sprites to the right position

			genPtrs[i]->mbackground->setPosition(shifted, -1200.0f);

			mBackground[i]->setPosition(shifted, genPtrs[i]->mbackground->getPosition()->y - 1800.0f);

			//Get the random 
			enemySpawn = getRangedRandom(0, 5);
			
			powerUpSpawn = getRangedRandom(0, 20);


			
			

			//Chance spawn ins
			if (enemySpawn <= 2)
			{
				mEnemies[i]->GetSprite()->enableSprite();
				mEnemies[i]->GetSprite()->setPosition(shifted + 1200, genPtrs[i]->mbackground->getPosition()->y + 90);
			}

			if (enemySpawn > 2)
			{
				hazardSpawn = getRangedRandom(0, 5);
				
				//Hazard Spawn in
				if (hazardSpawn <= 2)
				{
					mHazards[i]->enableSprite();
					mHazards[i]->setPosition(shifted + 2500, genPtrs[i]->mbackground->getPosition()->y);
				}
			}
				

			

			//Power up Spawn in
			if (powerUpSpawn <= 2)
			{
				mPowerUps[i]->GetSprite()->enableSprite();


				mPowerUps[i]->SetPowerType(getRangedRandom(0, 3));
				mPowerUps[i]->GetSprite()->setPosition(shifted + 2000, genPtrs[i]->mbackground->getPosition()->y);
			}

			
		}

		mEnemies[i]->update(milliseconds, player->getWindow());

		mHazards[i]->updateSprite(milliseconds);

		mPowerUps[i]->update(milliseconds);


	}


	

}

//Renders all the map stuff
void MapGen::render(Sprite* player)
{
	

	for (int i = 0; i < MAP_NUMBERS; i++)
	{
		//i = getRangedRandom(0, (MAP_NUMBERS - 1));
		if (player->getPosition()->x < ((genPtrs[i]->mbackground->getPosition()->x + genPtrs[i]->mbackground->getWidth()) + 2000))
		{
			

			genPtrs[i]->mbackground->render();
			genPtrs[i]->mbackground->getCollider()->renderCollider();

			mBackground[i]->render();

			
			mEnemies[i]->GetSprite()->render();

			mHazards[i]->render();

			mPowerUps[i]->render();

		}

	}
}


//Self Explaintory Getters

Sprite* MapGen::GetSprite(int sprite)
{
	return genPtrs[sprite]->mbackground;
}

Sprite* MapGen::GetHazard(int sprite)
{
	return mHazards[sprite];
}

powerUps* MapGen::GetPowerUp(int sprite)
{
	return mPowerUps[sprite];
}

Sprite* MapGen::GetEnemy(int sprite)
{
	return mEnemies[sprite]->GetSprite();
}
