#include "Player.h"
Player::Player() {
	position_.x = kPlayerPosition.x;
	position_.y = kPlayerPosition.y;
	rotate_ = 0.0f;
	scale_ = { 1.0f,1.0f };
	radius_.x = 4;
	radius_.y = 32;
	size_.x = radius_.x * 2;
	size_.y = radius_.y * 2;

	vertex_.bottom = (float)-radius_.y;
	vertex_.top = (float)radius_.y;
	vertex_.left = (float)-radius_.x;
	vertex_.right = (float)radius_.x;

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

}

void Player::Update() {

	//カメラ
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, position_);
	wvpVpMatrix_ = MakewvpVpMatrix(worldMatrix_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);
}

void Player::Draw() {
	screenLeftTop_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix_);
	screenLeftBottom_ = Transform({ vertex_.left, vertex_.bottom }, wvpVpMatrix_);
	screenRightTop_ = Transform({ vertex_.right, vertex_.top }, wvpVpMatrix_);
	screenRightBottom_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix_);

	Novice::DrawQuad((int)screenLeftTop_.x, (int)screenLeftTop_.y, (int)screenRightTop_.x, (int)screenRightTop_.y, (int)screenLeftBottom_.x, (int)screenLeftBottom_.y, (int)screenRightBottom_.x, (int)screenRightBottom_.y, 0, 0, size_.x, size_.y, texture, WHITE);
}