#pragma once
#include "Ball.h"
#include "Player.h"

class Play
{
public:

	Play();

	~Play();

	void Update(char* keys, char* preKeys);
	
	void Draw();

private:
	Ball* ball_;
	Player* player_;

};

