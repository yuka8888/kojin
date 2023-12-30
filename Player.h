#pragma once
#include "mt.h"
#include "Const.h"

class Player
{
public:
	Player();

	void Update();

	void Draw();

private:
	int texture = Novice::LoadTexture("./images/bat.png");

	Vertex vertex_;
	Vector2 position_;
	float rotate_;
	Vector2 scale_;
	Vector2i radius_;
	Vector2i size_;

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

