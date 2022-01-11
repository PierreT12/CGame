#ifndef SPRITE_H
#define SPRITE_H

#include "baseTypes.h"
#include "GameObject.h"
//#include "Collider.h"


#include <windows.h>
#include "openGLFramework.h"

class Collider;
enum ColliderTag;

class Sprite : public GameObject
{

public:
	// xPosition, yPosition are the position on the display where the image will be rendered (bottom left corner)
	// width, height are the width and height along which the image is rendered
	// Sprite Layer is the layer in which the sprite would be rendered (z coordinate value for rendering different sprites at different distances from viewport)
	Sprite(float_t xPosition, float_t yPosition, uint16_t width, uint16_t height, char8_t* spriteName, uint16_t spriteLayer);
	~Sprite() {};

	// Initialize member variables
	void init(GL_Window* window);

	void updateSprite(DWORD milliseconds);

	void setRotation(float_t);
	float_t getRotation();

	virtual void render();

	//Changes Sprite to the one passed through
	void ChangeSprite(char8_t* newSpriteName);
	

	void enableSprite() { mSpriteEnabled = 1; }
	void disableSprite() { mSpriteEnabled = 0; }
	bool8_t getSpriteEnabled() { return mSpriteEnabled; }

	uint16_t getWidth() { return mWidth; }
	uint16_t getHeight() { return mHeight; }
	void setWidth(uint16_t newWidth) { mWidth = newWidth; }
	void setHeight(uint16_t newHeight) { mHeight = newHeight; }

	// Create the associated box collider for the sprite with x,y offset from bottom left corner and given height and width
	void createCollider(int32_t x, int32_t y, int32_t width, int32_t height, ColliderTag, Sprite*);
	Collider* getCollider() { return mCollider; }


	bool8_t mIsGrounded = FALSE;
private:
	uint16_t mWidth;
	uint16_t mHeight;
	float_t mRotation;

	uint16_t mSpriteLayer;
	int16_t	mSpriteTextureID;


	bool8_t mSpriteEnabled;



	Collider* mCollider;
};

#endif
