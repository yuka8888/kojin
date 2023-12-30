#include "Play.h"

Play::Play() {
	ball_ = new Ball;
	player_ = new Player;
}

void Play::Update(char* keys, char preKeys[DIK_Q]) {
	if (keys[DIK_Q] && preKeys[DIK_Q] == 0) {
		ball_->IsMove_(true);
	}

	ball_->Update();
	player_->Update();
}

void Play::Draw() {
	ball_->Draw();
	player_->Draw();
}

Play::~Play() {
	delete ball_;
	delete player_;
}