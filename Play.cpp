#include "Play.h"

Play::Play() {
	ball_ = new Ball;
	player_ = new Player;
	bgTexture_ = Novice::LoadTexture("./images/bg.png");
	viewPortPositionAddCount_ = 0;
	isPanelMove_ = true;

	stage_ = 0;

	size_ = { 1280, 5120 };
	scale_ = { 1.0f, 1.0f };
	rotate_ = 0.0f;
	position_ = { 640.0f, 2305.0f };
	position2_ = { 1920.0f, 2305.0f };
	position3_ = { 3200.0f, 2305.0f };

	isNextScene_ = false;
	nextScene_ = TITLE;


	panelPosition_ = {};
	panelRadius_ = 256;
	firstPanelPosition_ = { kWindowWide / 2.0f, -600.0f };
	endPanelPosition_ = { kWindowWide / 2.0f, -200.0f };

	t_ = 0.0f;
	t2_ = 0.0f;
	t3_ = 0.0f;

	textureTimer_ = 0;

	clearHitNums_[0] = 1;
	clearHitNums_[1] = 2;
	clearHitNums_[2] = 3;
	clearHitNums_[3] = 3;
	clearHitNums_[4] = 4;

	clearMinScore_[0] = 10000;
	clearMinScore_[1] = 10000;
	clearMinScore_[2] = 20000;
	clearMinScore_[3] = 20000;
	clearMinScore_[4] = 40000;

	panelTexture_[0] = Novice::LoadTexture("./images/stage1.png");
	panelTexture_[1] = Novice::LoadTexture("./images/stage2.png");
	panelTexture_[2] = Novice::LoadTexture("./images/stage4.png");
	panelTexture_[3] = Novice::LoadTexture("./images/stage4.png");
	panelTexture_[4] = Novice::LoadTexture("./images/stage5.png");

	overPanelTexture_[0] = Novice::LoadTexture("./images/stage1over.png");
	overPanelTexture_[1] = Novice::LoadTexture("./images/stage2over.png");
	overPanelTexture_[2] = Novice::LoadTexture("./images/stage4over.png");
	overPanelTexture_[3] = Novice::LoadTexture("./images/stage4over.png");
	overPanelTexture_[4] = Novice::LoadTexture("./images/stage5over.png");

	scoreNumTexture[0] = Novice::LoadTexture("./images/0.png");
	scoreNumTexture[1] = Novice::LoadTexture("./images/1.png");
	scoreNumTexture[2] = Novice::LoadTexture("./images/2.png");
	scoreNumTexture[3] = Novice::LoadTexture("./images/3.png");
	scoreNumTexture[4] = Novice::LoadTexture("./images/4.png");
	scoreNumTexture[5] = Novice::LoadTexture("./images/5.png");

	clearTexture_ = Novice::LoadTexture("./images/clear.png");
	overTexture_ = Novice::LoadTexture("./images/over.png");
	nokoriTexture_ = Novice::LoadTexture("./images/nokori.png");
	allClearTexture_ = Novice::LoadTexture("./images/allClear.png");

	vertex_.bottom = (float)-size_.y / 2.0f;
	vertex_.top = (float)size_.y / 2.0f;
	vertex_.left = (float)-size_.x / 2.0f;
	vertex_.right = (float)size_.x / 2.0f;

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

void Play::Update(char* keys, char preKeys[DIK_Q]) {
	if (stage_ == 5 && ball_->GetIsStageClear() == true) {
		t_ += 0.01f;
		if (t_ >= 1.0f) {
			isNextScene_ = true;
			nextScene_ = TITLE;
		}
	}
	else if (isPanelMove_ == true) {
		if (stage_ == 0 && ball_->GetIsStageOver() == false && ball_->GetIsStageClear() == false) {
			if (t2_ >= 1.0f) {
				t3_ += 0.01f;
				panelPosition_ = Lerp({ firstPanelPosition_.x, -900.0f }, endPanelPosition_, easeInOutBack(t3_));
				if (t3_ >= 0.7f) {
					isPanelMove_ = false;
					textureTimer_ = 0;
					t3_ = 0.0f;
					t2_ = 0.0f;
					t_ = 0.0f;
				}
			}
			else if (t_ >= 1.0f) {
				t2_ += 0.01f;
			}
			else {
				t_ += 0.01f;
				panelPosition_ = Lerp(endPanelPosition_, firstPanelPosition_, EaseOutElastic(t_));
			}
		}
		else {
			if (t3_ > 0.0f) {
				t3_ += 0.01f;
				panelPosition_ = Lerp({ firstPanelPosition_.x, -900.0f }, endPanelPosition_, easeInOutBack(t3_));
				if (t3_ >= 0.7f) {
					isPanelMove_ = false;
					textureTimer_ = 0;
					ball_->SetIsStageClear(false);
					ball_->SetIsStageOver(false);
				}
			}
			else if (t_ >= 1.0f) {
				if (keys[DIK_Q]) {
					isNextScene_ = true;
					nextScene_ = TITLE;
					t3_ += 0.01f;
				}
				if (ball_->GetIsStageClear() == true) {
					if (keys[DIK_E]) {
						delete ball_;
						ball_ = new Ball;
						ball_->SetIsStageClear(true);
						t3_ += 0.01f;
					}
				}
				else if (ball_->GetIsStageOver() == true) {
					if (keys[DIK_E]) {
						delete ball_;
						ball_ = new Ball;
						ball_->SetIsStageOver(true);
						t3_ += 0.01f;
					}
				}
			}

			else {
				t_ += 0.01f;
				panelPosition_ = Lerp(endPanelPosition_, firstPanelPosition_, EaseOutElastic(t_));
			}
		}
		ball_->Draw();
		player_->Draw();
	}
	else {
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			player_->SetIsSwing(true);
		}

		ball_->SetIsHit(player_->GetIsHit());
		ball_->SetDistance(player_->GetDistance());
		ball_->Update(clearHitNums_[stage_], stage_, clearMinScore_[stage_]);

		if ((ball_->GetIsStageClear() == true || ball_->GetIsStageOver() == true) && textureTimer_ >= 60) {
			isPanelMove_ = true;
			t_ = 0.0f;
			t2_ = 0.0f;
			t3_ = 0.0f;
			if (ball_->GetIsStageClear() == true) {
				stage_++;
			}
		}

		if (ball_->GetPosition().x <= 0 && ball_->GetIsMove() == true) {
			ball_->SetIsHit(false);
			ball_->SetIsMove(false);
			ball_->SetVelocity({ 0.0f,0.0f });
			ball_->SetAcceleration({ 0.0f,0.0f });
			ball_->SetPitchTimer(120);
			player_->SetIsHit(false);
		}

		if (ball_->GetVelocity().x <= 0 && ball_->GetIsBound() == true && ball_->GetIsHit() == true) {
			ball_->SetIsHit(false);
			ball_->SetVelocity({ 0.0f,0.0f });
			ball_->SetAcceleration({ 0.0f,0.0f });
			ball_->SetPitchTimer(180);
			player_->SetIsHit(false);
		}

		if (ball_->GetPitchTimer() == 120) {
			position_ = { 640.0f, 2305.0f };
			position2_ = { 1920.0f, 2305.0f };
			position3_ = { 3200.0f, 2305.0f };
			viewPortPosition_ = {};
			ball_->SetViewPortPosition(viewPortPosition_);
		}

		player_->SetViewportPosition(ball_->GetViewPosition());
		player_->SetBallPosition(ball_->GetPosition());
		player_->Update();

		viewPortPosition_ = ball_->GetViewPosition();

		if (-viewPortPosition_.x >= position_.x + size_.x / 2.0f) {
			position_.x += size_.x * 3.0f;
		}
		else if (-viewPortPosition_.x >= position2_.x + size_.x / 2.0f) {
			position2_.x += size_.x * 3.0f;
		}
		else if (-viewPortPosition_.x >= position3_.x + size_.x / 2.0f) {
			position3_.x += size_.x * 3.0f;
		}
	}
	//カメラ
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, position_);
	worldMatrix2_ = MakeAffineMatrix(scale_, rotate_, position2_);
	worldMatrix3_ = MakeAffineMatrix(scale_, rotate_, position3_);
	wvpVpMatrix_ = MakewvpVpMatrix(worldMatrix_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);
	wvpVpMatrix2_ = MakewvpVpMatrix(worldMatrix2_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);
	wvpVpMatrix3_ = MakewvpVpMatrix(worldMatrix3_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);
}

void Play::Draw() {
	screenLeftTop_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix_);
	screenLeftBottom_ = Transform({ vertex_.left, vertex_.bottom }, wvpVpMatrix_);
	screenRightTop_ = Transform({ vertex_.right, vertex_.top }, wvpVpMatrix_);
	screenRightBottom_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix_);
	screenLeftTop2_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix2_);
	screenLeftBottom2_ = Transform({ vertex_.left, vertex_.bottom }, wvpVpMatrix2_);
	screenRightTop2_ = Transform({ vertex_.right, vertex_.top }, wvpVpMatrix2_);
	screenRightBottom2_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix2_);
	screenLeftTop3_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix3_);
	screenLeftBottom3_ = Transform({ vertex_.left, vertex_.bottom }, wvpVpMatrix3_);
	screenRightTop3_ = Transform({ vertex_.right, vertex_.top }, wvpVpMatrix3_);
	screenRightBottom3_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix3_);

	Novice::DrawQuad((int)screenLeftTop_.x, (int)screenLeftTop_.y, (int)screenRightTop_.x, (int)screenRightTop_.y, (int)screenLeftBottom_.x, (int)screenLeftBottom_.y, (int)screenRightBottom_.x, (int)screenRightBottom_.y, 0, 0, size_.x, size_.y, bgTexture_, WHITE);
	Novice::DrawQuad((int)screenLeftTop2_.x, (int)screenLeftTop2_.y, (int)screenRightTop2_.x, (int)screenRightTop2_.y, (int)screenLeftBottom2_.x, (int)screenLeftBottom2_.y, (int)screenRightBottom2_.x, (int)screenRightBottom2_.y, 0, 0, size_.x, size_.y, bgTexture_, WHITE);
	Novice::DrawQuad((int)screenLeftTop3_.x, (int)screenLeftTop3_.y, (int)screenRightTop3_.x, (int)screenRightTop3_.y, (int)screenLeftBottom3_.x, (int)screenLeftBottom3_.y, (int)screenRightBottom3_.x, (int)screenRightBottom3_.y, 0, 0, size_.x, size_.y, bgTexture_, WHITE);

	ball_->Draw();
	player_->Draw();

	//Novice::ScreenPrintf(0, 140, "bgPosition1 = %.0lf", position_.x);
	//Novice::ScreenPrintf(0, 160, "bgPosition2 = %.0lf", position2_.x);
	//Novice::ScreenPrintf(0, 180, "bgPosition3 = %.0lf", position3_.x);

	Novice::DrawSprite(1060, 200, scoreNumTexture[5 - ball_->GetPitchNum()], 0.5f, 0.5f, 0.0f, WHITE);

	if (ball_->GetIsStageClear() == true) {
		textureTimer_++;

		if (textureTimer_ >= 60) {
			Novice::DrawSprite((int)panelPosition_.x - panelRadius_, (int)panelPosition_.y - panelRadius_, panelTexture_[stage_], 0.8f, 0.8f, 0.0f, WHITE);
		}
		else {
			Novice::DrawSprite(0, 0, clearTexture_, 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
	else if (ball_->GetIsStageOver() == true && ball_->GetIsMove() == false) {
		textureTimer_++;

		if (textureTimer_ >= 60) {
			Novice::DrawSprite((int)panelPosition_.x - panelRadius_, (int)panelPosition_.y - panelRadius_, overPanelTexture_[stage_], 0.8f, 0.8f, 0.0f, WHITE);
		}
		else {
			Novice::DrawSprite(0, 0, overTexture_, 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
	else if (stage_ == 0) {
		Novice::DrawSprite((int)panelPosition_.x - panelRadius_, (int)panelPosition_.y - panelRadius_, panelTexture_[stage_], 0.8f, 0.8f, 0.0f, WHITE);
	}
	if (stage_ == 5 && ball_->GetIsStageClear() == true) {
		Novice::DrawSprite(0, 0, allClearTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	}
}

Play::~Play() {
	delete ball_;
	delete player_;
}

void Play::Initialization() {
	delete ball_;
	delete player_;

	ball_ = new Ball;
	player_ = new Player;
	viewPortPositionAddCount_ = 0;
	isPanelMove_ = true;

	stage_ = 0;

	size_ = { 1280, 5120 };
	scale_ = { 1.0f, 1.0f };
	rotate_ = 0.0f;
	position_ = { 640.0f, 2305.0f };
	position2_ = { 1920.0f, 2305.0f };
	position3_ = { 3200.0f, 2305.0f };

	isNextScene_ = false;
	nextScene_ = TITLE;


	panelPosition_ = {};
	panelRadius_ = 256;
	firstPanelPosition_ = { kWindowWide / 2.0f, -600.0f };
	endPanelPosition_ = { kWindowWide / 2.0f, -200.0f };

	t_ = 0.0f;
	t2_ = 0.0f;
	t3_ = 0.0f;

	textureTimer_ = 0;

	clearHitNums_[0] = 1;
	clearHitNums_[1] = 2;
	clearHitNums_[2] = 3;
	clearHitNums_[3] = 3;
	clearHitNums_[4] = 4;

	clearMinScore_[0] = 10000;
	clearMinScore_[1] = 10000;
	clearMinScore_[2] = 20000;
	clearMinScore_[3] = 20000;
	clearMinScore_[4] = 40000;


	vertex_.bottom = (float)-size_.y / 2.0f;
	vertex_.top = (float)size_.y / 2.0f;
	vertex_.left = (float)-size_.x / 2.0f;
	vertex_.right = (float)size_.x / 2.0f;

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