#include "Title.h"

Title::Title() {
	bgTexture_ = Novice::LoadTexture("./images/bg.png");
	titleTexture_ = Novice::LoadTexture("./images/title.png");
	batTexture_ = Novice::LoadTexture("./images/bat.png");
	ballTexture_ = Novice::LoadTexture("./images/baseball.png");
	pushSpaceTexture_ = Novice::LoadTexture("./images/pushSpace.png");
	titlePosition_ = { 0,0 };
	theta_ = 0.0f;
	isNextScene_ = false;
	isPush_ = false;
}

void Title::Update(char* keys) {
	theta_ += 0.1f;


	if (keys[DIK_SPACE]) {
		isPush_ = true;
	}

	if (isPush_ == true) {
		titlePosition_.y -= 7;
		if (titlePosition_.y <= -700.0f) {
			isNextScene_ = true;
		}
	}
	else {
		titlePosition_.y = sinf(theta_) * 10.0f - 50.0f;
	}

}

void Title::Draw() {
	Novice::DrawSprite(0, -4145, bgTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite((int)titlePosition_.x, (int)titlePosition_.y, titleTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(196, 360, batTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(984, 404, ballTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(500, (int)titlePosition_.y + 500, pushSpaceTexture_, 1.0f, 1.0f, 0.0f, WHITE);
}

void Title::Initialization() {
	titlePosition_ = { 0,0 };
	theta_ = 0.0f;
	isNextScene_ = false;
	isPush_ = false;

}