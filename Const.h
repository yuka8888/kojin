#pragma once
#include "mt.h"

const int kWindowWide = 1280;
const int kWindowHeight = 720;
const float kGroundPositionY = 150.0f;

const int kStageNum = 5;
const int kPitchNum = 5;

const Vector2 kBallPosition = { 1000, 300 };
const Vector2 kBallEndPosition = { 200, 270 };
const Vector2 kPlayerPosition = { 200, 300 };

enum PitchType {
	NORMAL,
	FAST,
	CURVE,
	WAVE,
};

enum Scene {
	TITLE,
	PLAY,
};