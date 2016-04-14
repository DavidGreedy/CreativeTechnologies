#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

#include <DirectXMath.h>

using namespace DirectX;

class CameraController
{
public:
	CameraController();
	~CameraController();

	void SetPosition(XMFLOAT3 pos);
	void SetRotation(XMFLOAT3 rot);

	void GetPosition(XMFLOAT3& pos);
	void GetRotation(XMFLOAT3& rot);

	void SetFrameTime(float);

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveUpward();
	void MoveDownward();
	void LookLeft();
	void LookRight();
	void LookUpward();
	void LookDownward();

	void IncreaseMoveSpeed();
	void DecreaseMoveSpeed();

	float* GetMoveSpeed() { return &mMoveSpeed; }

private:
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;

	float mDeltaTime;
	float mMoveSpeed;
};

#endif