#pragma once
#include <Novice.h>
#include "mt.h"
#include "Const.h"

class Ball
{
public:

	Ball();

	void Update(int clearHitNum_, int stage, int clearMinScore);

	void Draw();

	void SetIsMove(bool isMove) { isMove_ = isMove; }

	void SetIsHit(bool isHit) { isHit_ = isHit; }

	void SetDistance(float distance) { distance_ = distance; }

	void SetVelocity(Vector2 velocity) { velocity_ = velocity; }

	void SetAcceleration(Vector2 acceleration) { acceleration_ = acceleration; }

	void SetIsNextStage(bool isNextStage) { isNextStage_ = isNextStage; }
	
	void SetIsStageClear(bool isStageClear) { isStageClear_ = isStageClear; }
	
	void SetIsStageOver(bool isStageOver) { isStageOver_ = isStageOver; }

	void SetPitchTimer(int pitchTimer) { pitchTimer_ = pitchTimer; }

	void SetViewPortPosition(Vector2 viewPortPosition) { viewPortPosition_ = viewPortPosition; }

	Vector2 GetViewPosition() { return viewPortPosition_; }

	Vector2 GetPosition() { return position_; }

	Vector2 GetVelocity() { return velocity_; }

	bool GetIsStageClear() { return isStageClear_; }

	bool GetIsStageOver() { return isStageOver_; }

	bool GetIsBound() { return isBound_; }

	bool GetIsMove() { return isMove_; }

	bool GetIsHit() { return isHit_; }

	bool GetIsNextScene() { return isNextScene_; }

	Scene GetNextScene() { return nextScene_; }

	bool GetIsNextStage() { return isNextStage_; }
	
	int GetPitchTimer() { return pitchTimer_; }

	int GetPitchNum() { return pitchNum_; }

private:
	int texture;
	int scoreTexture;
	int highTexture;
	int scoreNumTexture[10];
	int kakeruTexture;

	Scene nextScene_;

	Vertex vertex_;
	Vector2 position_;
	Vector2 oldPosition_;
	Vector2 velocity_;
	Vector2 oldVelocity_;
	Vector2 acceleration_;
	int pitchTimer_;
	int pitchNum_;
	int hitNum_;
	float rotate_;
	Vector2 scale_;
	int radius_;
	int size_;
	bool isMove_;
	bool isOldMove_;
	bool isHit_;
	bool isOldHit_;
	bool isBound_;
	bool isNextStage_;
	bool isStageClear_;
	bool isStageOver_;
	bool isNextScene_;
	bool isNextPitch_;
	PitchType pitchType_;
	float amplitude;
	float theta_;
	float theta2_;
	int score_;
	int score2_;
	int scoreNum_[6];
	int highScore_;
	int highScore2_;
	int highScoreNum_[6];

	float distance_;



	//ベジエ曲線
	int bezieNum_;
	Vector2 beziePosition_;
	Vector2 beziePosition2_;
	float bezieTimer0_;
	float bezieTimer1_;
	int bezieCount_;
	int bezieCount2_;

	//カメラ
	Matrix3x3 worldMatrix_;
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
