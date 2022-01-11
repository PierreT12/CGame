#pragma once
class Player : public ObjectC
{

public:
	Player();
	Player(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY);
	~Player();

	void update(DWORD milliseconds);

private:
	bool isGrounded;



};

