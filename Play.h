#pragma once
#include "Ball.h"
#include "Player.h"

class Play
{
public:

	Play();

	~Play();

	void Update(char* keys, char* preKeys);

	void Initialization();

	void Draw();

	bool GetIsNextScene() { return isNextScene_; }

	Scene GetNextScene() { return nextScene_; }

private:
	Ball* ball_;
	Player* player_;
	float rotate_;
	Vector2 scale_;
	Vector2 position_;
	Vector2 position2_;
	Vector2 position3_;
	Vector2i size_;
	Vertex vertex_;
	int viewPortPositionAddCount_;

	int clearHitNums_[kStageNum];
	int clearMinScore_[kStageNum];
	int stage_;

	bool isNextScene_;
	Scene nextScene_;

	int bgTexture_;
	int panelTexture_[kStageNum];
	int overPanelTexture_[kStageNum];
	int clearTexture_;
	int overTexture_;
	int nokoriTexture_;
	int allClearTexture_;
	int scoreNumTexture[6];

	Vector2 firstPanelPosition_;
	Vector2 endPanelPosition_;
	Vector2 panelPosition_;
	int panelRadius_;

	float t_;
	float t2_;
	float t3_;

	int textureTimer_;

	bool isPanelMove_;

	//カメラ
	Matrix3x3 worldMatrix_;
	Matrix3x3 worldMatrix2_;
	Matrix3x3 worldMatrix3_;
	Matrix3x3 wvpVpMatrix_;
	Matrix3x3 wvpVpMatrix2_;
	Matrix3x3 wvpVpMatrix3_;
	Vector2 screenLeftTop_;
	Vector2 screenRightBottom_;
	Vector2 screenRightTop_;
	Vector2 screenLeftBottom_;
	Vector2 screenLeftTop2_;
	Vector2 screenRightBottom2_;
	Vector2 screenRightTop2_;
	Vector2 screenLeftBottom2_;
	Vector2 screenLeftTop3_;
	Vector2 screenRightBottom3_;
	Vector2 screenRightTop3_;
	Vector2 screenLeftBottom3_;
	Vertex cameraVertex_;
	Matrix3x3 cameraWorldMatrix_;
	Vector2 viewPortPosition_;
	Vector2 viewPortSize_;

};

