#include "Ball.h"


Ball::Ball() {
	velocity_ = { 0, 0 };
	acceleration_ = { 0,0 };
	rotate_ = 0.0f;
	scale_ = { 1.0f,1.0f };
	radius_ = 16;
	size_ = radius_ * 2;
	isMove_ = false;
	pitchType_ = CURVE;

	position_.x = kBallPosition.x;
	position_.y = kBallPosition.y;

	vertex_.bottom = (float)-radius_;
	vertex_.top = (float)radius_;
	vertex_.left = (float)-radius_;
	vertex_.right = (float)radius_;

	//カメラ
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

	//ベジエ曲線
	bezieNum = 40;
	beziePosition = { (kBallPosition.x + kPlayerPosition.x) / 2, 500 };
	bezieTimer0 = 0.0f;
	bezieTimer1 = 0.0f;
	bezieCount = 0;

}

void Ball::Update() {

	velocity_.x = 0;
	velocity_.y = 0;

	if (isMove_ == true) {
		rotate_ += 0.08f;

		switch (pitchType_) {
			case NORMAL:
				velocity_.x = -5.0f;
				break;

			case FAST:
				velocity_.x = -10.0f;
				break;

			case CURVE:
				bezieCount++;

				bezieTimer0 = bezieCount / float(bezieNum);
				bezieTimer1 = (bezieCount + 1) / float(bezieNum);

				position_ = Bezier(kPlayerPosition, beziePosition, kBallPosition, bezieTimer0);
				position_ = Bezier(kPlayerPosition, beziePosition, kBallPosition, bezieTimer1);

				if (position_.x <= 0) {
					isMove_ = false;
					bezieCount = 0;
					position_.x = kBallPosition.x;
					position_.y = kBallPosition.y;
				}
				break;
		}
	}

	position_.x += velocity_.x;
	position_.y += velocity_.y;

	//カメラ
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, position_);
	wvpVpMatrix_ = MakewvpVpMatrix(worldMatrix_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);

}

void Ball::Draw() {
	screenLeftTop_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix_);
	screenLeftBottom_ = Transform({ vertex_.left, vertex_.bottom }, wvpVpMatrix_);
	screenRightTop_ = Transform({ vertex_.right, vertex_.top }, wvpVpMatrix_);
	screenRightBottom_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix_);

	Novice::DrawQuad((int)screenLeftTop_.x, (int)screenLeftTop_.y, (int)screenRightTop_.x, (int)screenRightTop_.y, (int)screenLeftBottom_.x, (int)screenLeftBottom_.y, (int)screenRightBottom_.x, (int)screenRightBottom_.y, 0, 0, size_, size_, texture, WHITE);
}