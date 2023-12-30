#pragma once
#include <mt.h>
class CameraManager
{
public:
	CameraManager();

private:
	static Matrix3x3 cameraWorldMatrix_;

	static float cameraLeft_;
	static float cameraTop_;
	static float cameraRight_;
	static float cameraBottom_;

	static Vector2 viewPortPosition_;
	static Vector2 viewPortSize_;

};

