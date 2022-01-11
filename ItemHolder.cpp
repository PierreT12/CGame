#include "ItemHolder.h"
#include "powerUps.h"

//Constructor
ItemHolder::ItemHolder(Sprite* holder)
{
	mholderSprite = holder;

	mPowerUp = nullptr;
}


//Updates Holder
void ItemHolder::update(DWORD milliseconds)
{

	mholderSprite->updateSprite(milliseconds);
	
	if (mPowerUp != nullptr)
	{
		mPowerUp->GetSprite()->setPosition(mholderSprite->getPosition()->x + 50, mholderSprite->getPosition()->y + 50);
		mPowerUp->GetSprite()->updateSprite(milliseconds);
	}

}

//Renders Item Holder
void ItemHolder::render()
{

	mholderSprite->render();

	if (mPowerUp != nullptr)
	{
		mPowerUp->GetSprite()->render();
	}

}



//Getter/Setter

void ItemHolder::SetPowerUp(powerUps* power, GL_Window* window)
{

	mPowerUp = new powerUps(new Sprite(mholderSprite->getPosition()->x + 50, mholderSprite->getPosition()->y + 50, 300, 300, "MetaTest.png", 0), PowerType::INVALID_POWER);

	mPowerUp->GetSprite()->init(window);

	mPowerUp->SetPowerTypeManual(power->GetPowerType());

	power->GetSprite()->disableSprite();
}


void ItemHolder::ResetPoweUp()
{
	free(mPowerUp);
	mPowerUp = nullptr;
}

powerUps* ItemHolder::GetPowerUp()
{
	return mPowerUp;
}

Sprite* ItemHolder::GetHolder()
{
	return mholderSprite;
}
