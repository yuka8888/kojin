#pragma once
#include <mt.h>
#include <Const.h>

class Ball
{
public:

	Ball();

	void Update();

	void Draw();

	void IsMove_(bool isMove) { isMove_ = isMove };

private:

	Vertex vertex_;
	Vector2 position_;
	Vector2 velocity_;
	Vector2 acceleration_;
	int radius_;
	bool isMove_;
	PitchType pitchType_;

	Matrix3x3 worldMatrix_;
	Matrix3x3 vpVpMatrix_;
	Vector2 screenPosition_;
}

