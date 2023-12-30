#pragma once
#define _USE_MATH_DEFINES
#include "math.h"
#include <Novice.h>
#include <assert.h>

struct Vector2 final {
	float x;
	float y;
};

struct Vertex final {
	float left;
	float right;
	float top;
	float bottom;
};

struct ForCorners final {
	Vector2 topLeft;
	Vector2 topRight;
	Vector2 bottomLeft;
	Vector2 bottomRight;
};

struct Matrix2x2 final{
	float m[2][2];
};
struct Matrix3x3 final{
	float m[3][3];
};

struct Balls final{
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
};

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// �ŒZ����
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
float Length(Vector2 const& obj) {
	return sqrtf(obj.x * obj.x + obj.y * obj.y);
}

/// <summary>
/// ���K��
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
Vector2 Normalize(Vector2 const& obj) {
	float length = 0;
	Vector2 newObj = {};

	length = Length(obj);

	newObj.x = obj.x;
	newObj.y = obj.y;

	if (length != 0.0f) {
		newObj.x = obj.x / length;
		newObj.y = obj.y / length;
	}
	return newObj;
}

/// <summary>
/// ����
/// </summary>
/// <param name="obj1"></param>
/// <param name="obj2"></param>
/// <returns></returns>
float DotProduct(Vector2 const& obj1, Vector2 const& obj2) {
	return obj1.x * obj2.x + obj1.y * obj2.y;
}

/// <summary>
/// �O��
/// </summary>
/// <param name="obj1"></param>
/// <param name="obj2"></param>
/// <returns></returns>
float CrossProduct(Vector2 const& obj1, Vector2 const& obj2) {
	return obj1.x * obj2.y - obj1.y * obj2.x;
}

/// <summary>
/// ��]
/// </summary>
/// <param name="obj">�I�u�W�F�N�g�̎l���̍��W</param>
/// <param name="num">������1�Ή�]�����邩</param>
/// <returns></returns>
ForCorners Rotate(ForCorners const& obj, float const& num) {
	ForCorners newObj = {};

	float theta = 1.0f / num * float(M_PI);
	newObj.bottomLeft.x = obj.bottomLeft.x * cosf(theta) - obj.bottomLeft.y * sinf(theta);
	newObj.bottomLeft.y = obj.bottomLeft.y * cosf(theta) + obj.bottomLeft.x * sinf(theta);
	newObj.bottomRight.x = obj.bottomRight.x * cosf(theta) - obj.bottomRight.y * sinf(theta);
	newObj.bottomRight.y = obj.bottomRight.y * cosf(theta) + obj.bottomRight.x * sinf(theta);
	newObj.topLeft.x = obj.topLeft.x * cosf(theta) - obj.topLeft.y * sinf(theta);
	newObj.topLeft.y = obj.topLeft.y * cosf(theta) + obj.topLeft.x * sinf(theta);
	newObj.topRight.x = obj.topRight.x * cosf(theta) - obj.topRight.y * sinf(theta);
	newObj.topRight.x = obj.topRight.y * cosf(theta) + obj.topRight.x * sinf(theta);

	return newObj;
}

/// <summary>
/// �s��̉��Z
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix1.m[i][j] += matrix2.m[i][j];
		}
	}
	return matrix1;
}

/// <summary>
/// �s��̌��Z
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix1.m[i][j] -= matrix2.m[i][j];
		}
	}
	return matrix1;
}

/// <summary>
/// �s��̐�
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 matrix3 = {};

	matrix3.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	matrix3.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	matrix3.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	matrix3.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	matrix3.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	matrix3.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	matrix3.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	matrix3.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	matrix3.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];
	return matrix3;
}

/// <summary>
/// �s��̐�
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 matrix3 = {};

	matrix3.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0];
	matrix3.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1];
	matrix3.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0];
	matrix3.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1];
	return matrix3;
}

/// <summary>
/// �x�N�g���ƍs��̐�
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 obj = {};
	obj.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	obj.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];

	return obj;
}

/// <summary>
/// �t�s��
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix2x2 Inverse(Matrix2x2 matrix) {
	Matrix2x2 matrix2 = {};
	float num = 1.0f / (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	matrix2.m[0][0] = num * matrix.m[1][1];
	matrix2.m[0][1] = num * -matrix.m[0][1];
	matrix2.m[1][0] = num * -matrix.m[1][0];
	matrix2.m[1][1] = num * matrix.m[0][0];

	return matrix2;
}

/// <summary>
/// �t�s��
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 matrix2 = {};
	float num = 1.0f / (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][1] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	matrix2.m[0][0] = num * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	matrix2.m[0][1] = num * (-(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]));
	matrix2.m[0][2] = num * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	matrix2.m[1][0] = num * (-(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));
	matrix2.m[1][1] = num * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	matrix2.m[1][2] = num * (-(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]));
	matrix2.m[2][0] = num * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	matrix2.m[2][1] = num * (-(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]));
	matrix2.m[2][2] = num * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return matrix2;
}

/// <summary>
/// ��]�s��
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 matrix = {};
	matrix.m[0][0] = float(cos(theta));
	matrix.m[0][1] = float(sin(theta));
	matrix.m[1][0] = -1.0f * float(sin(theta));
	matrix.m[1][1] = float(cos(theta));
	return matrix;
}

/// <summary>
/// ��]�s��
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
Matrix3x3 MakeRotateMatrix3x3(float theta) {
	Matrix3x3 matrix = {};
	matrix.m[0][0] = float(cos(theta));
	matrix.m[0][1] = float(sin(theta));
	matrix.m[1][0] = -1.0f * float(sin(theta));
	matrix.m[1][1] = float(cos(theta));
	matrix.m[2][2] = 1;
	return matrix;
}

/// <summary>
/// ���s�ړ��s��̍쐬
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix3x3 MakeTransLateMatrix(Vector2 translate) {
	Matrix3x3 matrix = {};
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[2][0] = translate.x;
	matrix.m[2][1] = translate.y;

	return matrix;
}

/// <summary>
/// �g��k���s��̍쐬
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix3x3 MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 matrix = {};
	matrix.m[0][0] = scale.x;
	matrix.m[1][1] = scale.y;
	matrix.m[2][2] = 1;
	return matrix;
}

/// <summary>
/// �A�t�B���s��
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	return Multiply(Multiply(MakeScaleMatrix(scale), MakeRotateMatrix3x3(rotate)), MakeTransLateMatrix(translate));
}

/// <summary>
/// 2�����x�N�g���𓯎����W�ɕϊ�
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result = {};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0);

	result.x /= w;
	result.y /= w;

	return result;
}

/// <summary>
/// �]�u�s������߂�
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix2x2 Transpose(Matrix2x2 matrix) {
	Matrix2x2 matrix2 = {};

	matrix2.m[0][0] = matrix.m[0][0];
	matrix2.m[0][1] = matrix.m[1][0];
	matrix2.m[1][0] = matrix.m[0][1];
	matrix2.m[1][1] = matrix.m[1][1];

	return matrix2;
}

/// <summary>
/// �]�u�s������߂�
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix3x3 Transpose(Matrix3x3 matrix) {
	Matrix3x3 matrix2 = {};

	matrix2.m[0][0] = matrix.m[0][0];
	matrix2.m[0][1] = matrix.m[1][0];
	matrix2.m[0][2] = matrix.m[2][0];
	matrix2.m[1][0] = matrix.m[0][1];
	matrix2.m[1][1] = matrix.m[1][1];
	matrix2.m[1][2] = matrix.m[2][1];
	matrix2.m[2][0] = matrix.m[0][2];
	matrix2.m[2][1] = matrix.m[1][2];
	matrix2.m[2][2] = matrix.m[2][2];

	return matrix2;
}

/// <summary>
/// 2x2�s��̕\��
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 3x3�s��̕\��
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// ���ˉe�s��
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <returns></returns>
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 matrix = {};

	matrix.m[0][0] = 2.0f / (right - left);
	matrix.m[1][1] = 2.0f / (top - bottom);
	matrix.m[2][0] = (left + right) / (left - right);
	matrix.m[2][1] = (top + bottom) / (bottom - top);
	matrix.m[2][2] = 1.0f;

	return matrix;
}

/// <summary>
/// �r���[�|�[�g�s��
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 matrix = {};

	matrix.m[0][0] = width / 2.0f;
	matrix.m[1][1] = -height / 2.0f;
	matrix.m[2][0] = left + width / 2.0f;
	matrix.m[2][1] = top + height / 2.0f;
	matrix.m[2][2] = 1.0f;

	return matrix;
}

/// <summary>
/// �x�N�^�[�̕\��
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector"></param>
void VectorScreenPrintf(int x, int y, Vector2 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
}

/// <summary>
/// �X�N���[�����W�ϊ�
/// </summary>
/// <param name="position"></param>
/// <returns></returns>
Vector2 ScreenCoodinate(Vector2 position) {
	position.y = (position.y - 500) * -1;

	return position;
}

/// <summary>
/// ���`���
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
	return { t * a.x + (1.0f - t) * b.x, t * a.y + (1.0f - t) * b.y };
}

/// <summary>
/// 2���x�W�G�Ȑ���̓_�����߂�
/// </summary>
/// <param name="p0"></param>
/// <param name="pi"></param>
/// <param name="p2"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	Vector2 p0p1 = Lerp(p0, p1, t);

	Vector2 p1p2 = Lerp(p1, p2, t);

	return  Lerp(p0p1, p1p2, t);
}

/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="p0"></param>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="p3"></param>
/// <param name="t"></param>
/// <returns></returns>
Vector2 CatmullRom(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, float t) {
	Vector2 position = {};

	position.x = 1.0f / 2.0f * ((-p0.x + 3.0f * p1.x - 3 * p2.x + p3.x) * t * t * t +
		(2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t * t +
		(-p0.x + p2.x) * t +
		2 * p1.x);
	position.y = 1.0f / 2.0f * ((-p0.y + 3.0f * p1.y - 3 * p2.y + p3.y) * t * t * t +
		(2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t * t +
		(-p0.y + p2.y) * t +
		2 * p1.y);

	return position;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Matrix3x3 CoordinateTransformation(Matrix3x3 cameraWorldMatrix, Vertex cameraVertex, Vector2 viewPortPosition, Vector2 viewPortSize) {
	Matrix3x3 viewMatrix = Inverse(cameraWorldMatrix);
	Matrix3x3 orthoMatrix = MakeOrthographicMatrix(cameraVertex.left, cameraVertex.top, cameraVertex.right, cameraVertex.bottom);
	Matrix3x3 viewportMatrix = MakeViewportMatrix(viewPortPosition.x, viewPortPosition.y, viewPortSize.x, viewPortSize.y);

	Matrix3x3 vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	return vpVpMatrix = Multiply(vpVpMatrix, viewportMatrix);
}