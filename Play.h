#pragma once
#include "Ball.h"
class Play
{
public:

	Play();

	~Play();

	void Update(char* keys, char* preKeys);
	
	void Draw();

private:
	Ball* ball_;
	

};

