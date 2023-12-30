#include "Ball.h"


Ball::Ball() {
	velocity_ = {0, 0};
	acceleration_ = {0,0};
	radius_ = 16;
	isMove_ = false;
	pitchType_ = NORMAL;

	position_.x = kBallPosition.x;
	position_.y = kBallPosition.y;

	vertex_.bottom = (float) - radius_;
	vertex_.top = (float)radius_;
	vertex_.left = (float)-radius_;
	vertex_.right = (float)radius_;

	cameraWorldMatrix_.m[0][0] = 1;
	cameraWorldMatrix_.m[0][1] = 0;
	cameraWorldMatrix_.m[0][2] = 0;
	cameraWorldMatrix_.m[1][0] = 0;
	cameraWorldMatrix_.m[1][1] = 1;
	cameraWorldMatrix_.m[1][2] = 0;
	cameraWorldMatrix_.m[2][0] = 640;//
	cameraWorldMatrix_.m[2][1] = 360;//
	cameraWorldMatrix_.m[2][2] = 1;

	cameraVertex_.left = -640;
	cameraVertex_.top = 360;
	cameraVertex_.right = 640;
	cameraVertex_.bottom = -360;

	viewPortPosition_ = {};
	viewPortSize_ = { 1280.0f, 720.0f };

}

void Ball::Update() {

	velocity_.x = 0;
	velocity_.y = 0;

	if (isMove_ == true) {
		switch (pitchType_) {
			case NORMAL:
				velocity_.x = -5.0f;
				break;

			case FAST:
				velocity_.x = -10.0f;
				break;

			case CURVE:
				break;
		}
	}

	position_.x += velocity_.x;
	position_.y += velocity_.y;

	worldMatrix_ = MakeAffineMatrix({ 1.0f,1.0f }, 0.0f, position_);
	wvpVpMatrix_ = MakewvpVpMatrix(worldMatrix_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);

}

void Ball::Draw() {
	screenLeftTop_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix_);
	screenRightBottom_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix_);

	Novice::DrawQuad((int)screenLeftTop_.x, (int)screenLeftTop_.y, (int)screenRightBottom_.x, (int)screenLeftTop_.y, (int)screenLeftTop_.x, (int)screenRightBottom_.y, (int)screenRightBottom_.x, (int)screenRightBottom_.y, 0, 0, 32, 32, texture, WHITE);
}