﻿#pragma once
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
	int hd = Novice::LoadTexture("white1x1.png");


	Vertex vertex_;
	Vector2 position_;
	Vector2 velocity_;
	Vector2 acceleration_;
	float rotate_;
	Vector2 scale_;
	int radius_;
	int size_;
	bool isMove_;
	PitchType pitchType_;

	//ベジエ曲線
	int bezieNum;
	Vector2 beziePosition;
	float bezieTimer0;
	float bezieTimer1;
	int bezieCount;

	//カメラ
	Matrix3x3 worldMatrix_;
	Matrix3x3 wvpVpMatrix_;
	Vector2 screenLeftTop_;
	Vector2 screenRightBottom_;
	Vector2 screenRightTop_;
	Vector2 screenLeftBottom_;
	Vertex cameraVertex_;
	Matrix3x3 cameraWorldMatrix_;
	Vector2 viewPortPosition_;
	Vector2 viewPortSize_;

};
