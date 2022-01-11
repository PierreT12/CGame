#include "Score.h"

//Score Constructor
Score::Score(Sprite* namePlate, bool8_t player)
{
	mNamePlate = namePlate;

	mPlayer = player;
	
	mactualScore = 0;

	mTimer = 200.0f;
	mplaces = (Sprite**)malloc(4 * sizeof(Sprite*));

	mlastScore = 0;


	mIsPlayerDead = FALSE;
};


//Score initailization 
void Score::init(GL_Window* window)
{

	//Allocating 4 Sprites for the digits
	
	for (int i = 0; i < 4; i++)
	{
		mplaces[i] = new Sprite(mNamePlate->getPosition()->x, mNamePlate->getPosition()->y, 100, 250, "Sprites\\ScoreNumbs\\0.png", 0);
		mplaces[i]->init(window);
	}

}



//Update
void Score::update(DWORD milliseconds)
{
	if (mTimer <= 0 && mIsPlayerDead == FALSE)
	{
		AddtoScore(1);
		mTimer = 200.0f;
	}
	else
	{
		mTimer -= 1.0f;
	}
	

	//Setting score sprites if needed
	if (mlastScore != mactualScore)
	{
		setScoreValues();
	}
	

	
	if (mIsPlayerDead == FALSE)
	{
		//Setting score positions
		mplaces[0]->setPosition(mNamePlate->getPosition()->x + 900, mNamePlate->getPosition()->y + 140);
		mplaces[1]->setPosition(mNamePlate->getPosition()->x + 1020, mNamePlate->getPosition()->y + 140);
		mplaces[2]->setPosition(mNamePlate->getPosition()->x + 1140, mNamePlate->getPosition()->y + 140);
		mplaces[3]->setPosition(mNamePlate->getPosition()->x + 1260, mNamePlate->getPosition()->y + 140);
	}
	//Setting the place ppositions for the Game Over Screen
	else
	{
		//Player 1
		if (mPlayer == TRUE)
		{
			mplaces[0]->setPosition(-850, -1775);
			mplaces[1]->setPosition(-730, -1775);
			mplaces[2]->setPosition(-610, -1775);
			mplaces[3]->setPosition(-490, -1775);



		}
		//Player 2
		else
		{

			mplaces[0]->setPosition(1150, -1775);
			mplaces[1]->setPosition(1270, -1775);
			mplaces[2]->setPosition(1390, -1775);
			mplaces[3]->setPosition(1510, -1775);

		}
	}
	

	for (int i = 0; i < 4; i++)
	{
		mplaces[i]->updateSprite(milliseconds);
	}


	mlastScore = mactualScore;
}

//Render Loop
void Score::render()
{
	for (int i = 0; i < 4; i++)
	{
		mplaces[i]->render();
	}


}


//Adds number to score
void Score::AddtoScore(int16_t numbToAdd)
{
	mactualScore += numbToAdd;
}



//Getter/Setter
void Score::SetSpriteNumb(int* numb, char* file)
{
	file[0] = *numb + '0';
	file[1] = '.';
	file[2] = 'p';
	file[3] = 'n';
	file[4] = 'g';
	file[5] = '\0';

}

Sprite* Score::getSpritePlate()
{
	return mNamePlate;
}

int16_t Score::GetActualScore()
{
	return mactualScore;
}

void Score::setScoreValues()
{

	int fakeScore = mactualScore;

	char* mainPath = (char*)malloc(150);

	strcpy(mainPath, "Sprites\\ScoreNumbs\\");

	char filePath[6];

	//We need to set the 1000's place
	if (fakeScore > 999)
	{
		int thousand = 0;
		do
		{
			fakeScore -= 1000;

			thousand += 1;

		} while (fakeScore > 999);

		strcpy(mainPath, "Sprites\\ScoreNumbs\\");
		SetSpriteNumb(&thousand, filePath);
		strcat(mainPath, filePath);

		mplaces[0]->ChangeSprite(mainPath);

	}
	else
	{
		mplaces[0]->ChangeSprite("Sprites\\ScoreNumbs\\0.png");
	}

	//Checking 100's digit
	if (fakeScore > 99)
	{
		int hundrends = 0;
		do
		{
			fakeScore -= 100;

			hundrends += 1;

		} while (fakeScore > 99);

		strcpy(mainPath, "Sprites\\ScoreNumbs\\");
		SetSpriteNumb(&hundrends, filePath);
		strcat(mainPath, filePath);
		mplaces[1]->ChangeSprite(mainPath);
	}
	else
	{
		mplaces[1]->ChangeSprite("Sprites\\ScoreNumbs\\0.png");
	}

	//Checking 10's place
	if (fakeScore > 9)
	{
		int tenths = 0;
		do
		{
			fakeScore -= 10;

			tenths += 1;

		} while (fakeScore > 9);

		strcpy(mainPath, "Sprites\\ScoreNumbs\\");
		SetSpriteNumb(&tenths, filePath);
		strcat(mainPath, filePath);
		mplaces[2]->ChangeSprite(mainPath);
	}
	else
	{
		mplaces[2]->ChangeSprite("Sprites\\ScoreNumbs\\0.png");
	}

	strcpy(mainPath, "Sprites\\ScoreNumbs\\");
	SetSpriteNumb(&fakeScore, filePath);
	strcat(mainPath, filePath);
	//Set the 1's place
	mplaces[3]->ChangeSprite(mainPath);

}