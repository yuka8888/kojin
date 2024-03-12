#pragma once
#include <Novice.h>
#include <math.h>
#include "mt.h"
#include "Const.h"

class Title
{
public:
	Title();

	void Update(char* keys);

	void Draw();

	void Initialization();

	bool GetIsNextScene() { return isNextScene_; }


private:
	int bgTexture_;
	int titleTexture_;
	int batTexture_;
	int ballTexture_;
	int pushSpaceTexture_;

	bool isPush_;

	Vector2 titlePosition_;
	float theta_;

	bool isNextScene_;
};

