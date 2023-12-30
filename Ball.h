#pragma once
#include <Novice.h>
#include "mt.h"
#include "Const.h"

class Ball
{
public:

	Ball();

	void Update();

	void Draw();

	void IsMove_(bool isMove) { isMove_ = isMove; }

private:
	int texture = Novice::LoadTexture("./images/baseball.png");

	Vertex cameraVertex_;
	Matrix3x3 cameraWorldMatrix_;
	Vector2 viewPortPosition_;
	Vector2 viewPortSize_;

	Vertex vertex_;
	Vector2 position_;
	Vector2 velocity_;
	Vector2 acceleration_;
	int radius_;
	bool isMove_;
	PitchType pitchType_;

	Matrix3x3 worldMatrix_;
	Matrix3x3 wvpVpMatrix_;
	Vector2 screenLeftTop_;
	Vector2 screenRightBottom_;
};
