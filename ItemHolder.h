#ifndef ITEM_HOLDER_H
#define ITEM_HOLDER_H
#pragma once
#include "openglframework.h"
#include "baseTypes.h"
#include "Sprite.h"
#include "powerUps.h"
class ItemHolder
{
private:
	Sprite* mholderSprite;

	//Might need to change to the item class
	powerUps* mPowerUp;




public:

	ItemHolder(Sprite* holder);

	void SetPowerUp(powerUps* power, GL_Window* window);

	void update(DWORD milliseconds);

	void render();

	void ResetPoweUp();

	powerUps* GetPowerUp();

	Sprite* GetHolder();

};
#endif
