#include "Play.h"

Play::Play() {
	ball_ = new Ball;
}

void Play::Update(char* keys, char preKeys[DIK_Q]) {
	if (keys[DIK_Q] && preKeys[DIK_Q] == 0) {
		ball_->IsMove_(true);
	}

	ball_->Update();
}

void Play::Draw() {
	ball_->Draw();
}

Play::~Play() {
	delete ball_;
}