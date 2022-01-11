#include "Generation.h"
#include "MainPlayers.h"
#include "MapGen.h"
class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene(GL_Window* window);
	void UpdateFrame(DWORD milliseconds, GL_Window* window);
	void DestroyGame();
	void init(GL_Window* window);
	void shutdown();
	//static const uint32_t mScreenWidth = 1024;
	//static const uint32_t mScreenHeight = 768;
	//static const uint32_t mBitsPerPixel = 32;

	//Slows down the player that uses this item
	void SlowDown(bool8_t* ourPlayer, float_t *speed);

	//Speeds the opposing player up
	void SpeedUp(bool8_t* ourPlayer,  float_t* speed);

	//Will make the player who used it Invincible for a short time
	void Invincible(bool8_t* ourPlayer);

	//Makes the opposing player bigger
	void Bigger(bool8_t* ourPlayer);

	MainPlayers* GetPlayerOne() { return playerOne; }
	MainPlayers* GetPlayerTwo() { return playerTwo; }
private:
	static const char8_t mGameTitle[30];
	static CGame *sInstance;

	//Maps
	MapGen* playerOneMap;
	MapGen* playerTwoMap;

	//Players
	MainPlayers* playerOne;
	MainPlayers* playerTwo;

	//Scores
	Score* kirbyScore;
	Score* metaScore;

	//Attacks
	Attack* kirbyAttack;
	Attack* metaAttack;

	//Item Holders
	ItemHolder* kirbyHolder;
	ItemHolder* metaHolder;


	CGame(){};

};