#include "Ball.h"


Ball::Ball() {
	texture = Novice::LoadTexture("./images/baseball.png");
	scoreTexture = Novice::LoadTexture("./images/score.png");
	highTexture = Novice::LoadTexture("./images/high.png");
	kakeruTexture = Novice::LoadTexture("./images/kakeru.png");

	scoreNumTexture[0] = Novice::LoadTexture("./images/0.png");
	scoreNumTexture[1] = Novice::LoadTexture("./images/1.png");
	scoreNumTexture[2] = Novice::LoadTexture("./images/2.png");
	scoreNumTexture[3] = Novice::LoadTexture("./images/3.png");
	scoreNumTexture[4] = Novice::LoadTexture("./images/4.png");
	scoreNumTexture[5] = Novice::LoadTexture("./images/5.png");
	scoreNumTexture[6] = Novice::LoadTexture("./images/6.png");
	scoreNumTexture[7] = Novice::LoadTexture("./images/7.png");
	scoreNumTexture[8] = Novice::LoadTexture("./images/8.png");
	scoreNumTexture[9] = Novice::LoadTexture("./images/9.png");

	oldPosition_ = {};
	velocity_ = { 0, 0 };
	oldVelocity_ = { 0, 0 };
	acceleration_ = { 0,0 };
	rotate_ = 0.0f;
	scale_ = { 1.0f,1.0f };
	radius_ = 16;
	size_ = radius_ * 2;
	pitchTimer_ = 120;
	pitchNum_ = 0;
	hitNum_ = 0;
	isMove_ = false;
	isOldMove_ = false;
	isHit_ = false;
	isOldHit_ = false;
	isBound_ = false;
	pitchType_ = CURVE;
	amplitude = 50.0f;
	theta_ = 0.0f;
	theta2_ = 0.0f;
	distance_ = 0.0f;
	isNextStage_ = false;
	isStageClear_ = false;
	isStageOver_ = false;
	isNextPitch_ = true;
	score_ = 0;
	score2_ = 0;
	highScore_ = 0;
	highScore2_ = 0;
	nextScene_ = TITLE;
	for (int i = 0; i < 6; i++) {
		scoreNum_[i] = 0;
		highScoreNum_[i] = 0;
	}

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
	bezieNum_ = 40;
	beziePosition_ = { (kBallPosition.x + kPlayerPosition.x) / 2.0f, 500.0f };
	beziePosition2_ = { 0,0 };
	bezieTimer0_ = 0.0f;
	bezieTimer1_ = 0.0f;
	bezieCount_ = 0;
	bezieCount2_ = 0;

}

void Ball::Update(int clearHitNum, int stage, int clearMinScore) {

	if (stage == 0) {
		pitchType_ = NORMAL;
	}
	else if (stage == 1) {
		pitchType_ = FAST;
	}
	else if (stage == 2) {
		pitchType_ = CURVE;
	}
	else if (stage == 3) {
		pitchType_ = WAVE;
	}
	else if (stage == 4) {
		pitchType_ = WAVE;
	}

	if (isHit_ == false) {
		pitchTimer_--;
		if (pitchTimer_ == 0) {
			isMove_ = true;
			isNextPitch_ = true;
			pitchNum_++;
		}
		else if (pitchTimer_ == 120) {
			isBound_ = false;
			isMove_ = false;
		}
	}


	//球種ごとの動き
	if (isMove_ == true && isHit_ == false && isNextPitch_ == true) {
		//rotate_ += 0.08f;

		switch (pitchType_) {
			case NORMAL:
				velocity_.x = -7.0f;
				//viewPortPosition_.x -= velocity_.x;

				break;

			case FAST:
				velocity_.x = -12.0f;
				//viewPortPosition_.x -= velocity_.x;

				break;

			case CURVE:
				bezieCount_++;
				beziePosition_.x = (kBallPosition.x + kBallEndPosition.x) / 2.0f;
				beziePosition_.y = 500.0f;

				bezieTimer0_ = bezieCount_ / float(bezieNum_);
				bezieTimer1_ = (bezieCount_ + 1) / float(bezieNum_);


				position_ = Bezier(kBallEndPosition, beziePosition_, kBallPosition, bezieTimer0_);
				position_ = Bezier(kBallEndPosition, beziePosition_, kBallPosition, bezieTimer1_);

				//viewPortPosition_.x += oldPosition_.x - position_.x;

				break;

			case WAVE:
				theta_ += 0.1f;
				theta2_ += 0.2f;
				velocity_.x = -9.7f;

				position_.y = sinf(theta_) * amplitude + cosf(theta2_) * amplitude + kBallPosition.y;

				//viewPortPosition_.x -= velocity_.x;

				theta_ += float(M_PI) / 60.0f;
				break;
		}
	}

	//ボールが打たれた瞬間
	if (isHit_ == true && isOldHit_ == false) {
		velocity_.x = (30 / distance_) * 220;
		velocity_.y = (30 / distance_) * 100;
		oldVelocity_.x = velocity_.x;
		oldVelocity_.y = velocity_.y;
		acceleration_.x = -(velocity_.x / 250.0f);
		acceleration_.y = -(velocity_.y / 50.0f);
		isNextPitch_ = false;
		hitNum_++;
	}

	//バットで打ってボールが飛んでいく
	if (isHit_ >= true && isBound_ == false) {
		//地面についたとき
		if (position_.y <= kGroundPositionY) {
			isBound_ = true;
			velocity_.y = oldVelocity_.y / 3.0f;
			oldVelocity_.x = velocity_.x;
			oldVelocity_.y = velocity_.y;
			acceleration_.x = -(velocity_.x / 150.0f);
			acceleration_.y = -(velocity_.y / 30.0f);

		}

	}
	else if (isBound_ == true) {

		if (position_.y <= kGroundPositionY) {
			viewPortPosition_.y += kGroundPositionY - position_.y;
			velocity_.y = oldVelocity_.y / 3.0f;
			oldVelocity_.y = velocity_.y;
			position_.y = kGroundPositionY;
			acceleration_.y = -(velocity_.y / 20.0f);
		}

		if (velocity_.x <= 0.0f && isHit_ == true) {
			pitchTimer_ = 180;
			acceleration_.x = 0.0f;
			velocity_.x = 0.0f;
		}
		if (oldVelocity_.y <= 1.0f) {
			acceleration_.y = 0.0f;
			velocity_.y = 0.0f;
			oldVelocity_.y = velocity_.y;
		}
	}

	//飛んでいる間の回転
	if (isMove_ == true) {
		rotate_ -= velocity_.x / 100.0f;
	}

	if ((isOldMove_ == true && isMove_ == false)) {
		theta_ = 0.0f;
		bezieCount_ = 0;
		bezieCount2_ = 0;
		position_.x = kBallPosition.x;
		position_.y = kBallPosition.y;
		viewPortPosition_ = {};
	}

	isOldHit_ = isHit_;
	isOldMove_ = isMove_;

	velocity_.x += acceleration_.x;
	velocity_.y += acceleration_.y;

	oldPosition_.x = position_.x;
	oldPosition_.y = position_.y;

	position_.x += velocity_.x;
	position_.y += velocity_.y;

	//スコア
	highScore_ = highScore2_;
	if (isHit_ == true) {
		score_ = (int)position_.x;
		score2_ = (int)position_.x;
	}

	if (score_ > highScore_) {
		highScore_ = score_;
		highScore2_ = score_;
	}

	for (int i = 5; i >= 0; i--) {
		scoreNum_[i] = score_ % 10;
		score_ = score_ / 10;
		highScoreNum_[i] = highScore_ % 10;
		highScore_ = highScore_ / 10;
	}

	if ((isHit_ >= true && isBound_ == false) || isBound_ == true) {
		viewPortPosition_.x -= velocity_.x;
		viewPortPosition_.y += velocity_.y;
	}

	if (clearHitNum <= hitNum_ && clearMinScore <= highScore2_ && pitchTimer_ == 120) {
		isStageClear_ = true;
	}

	if (pitchNum_ >= kPitchNum) {
		isStageOver_ = true;
	}


	//カメラ

}

void Ball::Draw() {
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, position_);
	wvpVpMatrix_ = MakewvpVpMatrix(worldMatrix_, cameraWorldMatrix_, cameraVertex_, viewPortPosition_, viewPortSize_);

	screenLeftTop_ = Transform({ vertex_.left, vertex_.top }, wvpVpMatrix_);
	screenLeftBottom_ = Transform({ vertex_.left, vertex_.bottom }, wvpVpMatrix_);
	screenRightTop_ = Transform({ vertex_.right, vertex_.top }, wvpVpMatrix_);
	screenRightBottom_ = Transform({ vertex_.right, vertex_.bottom }, wvpVpMatrix_);

	Novice::DrawQuad((int)screenLeftTop_.x, (int)screenLeftTop_.y, (int)screenRightTop_.x, (int)screenRightTop_.y, (int)screenLeftBottom_.x, (int)screenLeftBottom_.y, (int)screenRightBottom_.x, (int)screenRightBottom_.y, 0, 0, size_, size_, texture, WHITE);

	//スコア
	Novice::DrawSprite(800, 20, scoreTexture, 1.0f, 1.0f, 0.0f, WHITE);
	for (int i = 0; i < 6; i++) {
		Novice::DrawSprite(1000 + i * 45, 20, scoreNumTexture[scoreNum_[i]], 1.0f, 1.0f, 0.0f, WHITE);
	}

	//ハイスコア
	Novice::DrawSprite(800, 90, scoreTexture, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(600, 90, highTexture, 1.0f, 1.0f, 0.0f, WHITE);
	for (int i = 0; i < 6; i++) {
		Novice::DrawSprite(1000 + i * 45, 90, scoreNumTexture[highScoreNum_[i]], 1.0f, 1.0f, 0.0f, WHITE);
	}

	Novice::DrawSprite(1000, 200, texture, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite(1020, 185, kakeruTexture, 1.0f, 1.0f, 0.0f, WHITE);

#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "ballPosition.x = %f", position_.x);
	Novice::ScreenPrintf(0, 20, "ballPosition.y = %f", position_.y);
	Novice::ScreenPrintf(0, 40, "velocity = (%lf %lf)", velocity_.x, velocity_.y);
	Novice::ScreenPrintf(0, 60, "acceleration.y = %f", acceleration_.y);
	Novice::ScreenPrintf(0, 80, "distance = %f", distance_);
	Novice::ScreenPrintf(0, 100, "isHit = %d", isHit_);
	Novice::ScreenPrintf(0, 120, "isMove = %d", isMove_);
	Novice::ScreenPrintf(300, 0, "pitchTimer = %d", pitchTimer_);

#endif
}