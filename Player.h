#pragma once
#include "mt.h"
#include "Const.h"
#include <cmath>

class Player
{
public:
	Player();

	void Update();

	void Draw();

	void SetIsSwing(bool isSwing) { isSwing_ = isSwing; }

	void SetIsHit(bool isHit) { isHit_ = isHit; }

	void SetViewportPosition(Vector2 viewportPosition) { viewPortPosition_ = viewportPosition; }
	
	void SetBallPosition(Vector2 ballPosition) { ballPosition_ = ballPosition; }

	bool GetIsHit() { return isHit_; }

	float GetDistance() { return distance_; }


private:
	int texture = Novice::LoadTexture("./images/bat.png");

	Vertex vertex_;
	Vector2 position_;
	float rotate_;
	Vector2 scale_;
	Vector2i radius_;
	Vector2i size_;
	float swingSpeed_;
	bool isSwing_;
	bool isHit_;

	float distance_;

	Vector2 ballPosition_;

	//カメラ
	Matrix3x3 worldMatrix_;
	Matrix3x3 translateMatrix_;
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
