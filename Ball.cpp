#include "Ball.h"

Ball::Ball() {
	velocity_ = {0, 0};
	acceleration_ = {0,0};
	radius_ = 16;
	isMove_ = false;
	pitchType_ = NORMAL;

	position_.x = kBallPosition.x;
	position_.y = kBallPosition.y;

	vertex_.bottom = position_.y - radius_;
	vertex_.top = position_.y + radius_;
	vertex_.left = position_.x - radius_;
	vertex_.right = position_.x + radius_;
}

void Ball::Update() {
	velocity_.x = 0;
	velocity_.y = 0;

	if (isMove_ == true) {
		switch (pitchType_) {
			case NORMAL:
				velocity_.x = 5.0f;
				break;

			case FAST:
				velocity_.x = 10.0f;
				break;

			case CURVE:
				break;
		}
		velocity_.x = 5.0f;
	}

	position_.x += velocity_.x;
	position_.y += velocity_.y;

	worldMatrix_ = MakeAffineMatrix(Vector2{ 1.0f,1.0f }, 0.0f, position_);
	Matrix3x3 wvpVpMatrix = Multiply(translateMatrix, vpVpMatrix);
}

void Ball::Draw() {
	screenPosition_
	Novice::DrawEllipse()
}