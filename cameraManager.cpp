#include "cameraManager.h"

CameraManager::CameraManager() {
	cameraWorldMatrix_.m[0][0] = 1;
	cameraWorldMatrix_.m[1][1] = 1;
	cameraWorldMatrix_.m[2][0] = 200;
	cameraWorldMatrix_.m[2][1] = 200;
	cameraWorldMatrix_.m[2][2] = 1;

	cameraLeft_ = -640;
	cameraTop_ = 360;
	cameraRight_ = 640;
	cameraBottom_ = -360;

	viewPortPosition_ = {};
	viewPortSize_ = { 1280.0f, 720.0f };

}