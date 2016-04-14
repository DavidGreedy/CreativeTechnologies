#include "CameraController.h"

CameraController::CameraController()
{
	mPosition = XMFLOAT3(0, 0, 0);
	mRotation = XMFLOAT3(0, 0, 0);

	mDeltaTime = 0.0f;
	mMoveSpeed = 1.0f;
}

CameraController::~CameraController()
{

}

void CameraController::SetPosition(XMFLOAT3 pos)
{
	mPosition = pos;
}

void CameraController::SetRotation(XMFLOAT3 rot)
{
	mRotation = rot;
}

void CameraController::GetPosition(XMFLOAT3& pos)
{
	pos = mPosition;
}

void CameraController::GetRotation(XMFLOAT3& rot)
{
	rot = mRotation;
}

void CameraController::SetFrameTime(float time)
{
	mDeltaTime = time;
}

void CameraController::MoveForward()
{
	mPosition.x += sinf(XMConvertToRadians(mRotation.y)) * mDeltaTime * mMoveSpeed;
	mPosition.z += cosf(XMConvertToRadians(mRotation.y)) * mDeltaTime * mMoveSpeed;
}

void CameraController::MoveBackward()
{
	mPosition.x -= sinf(XMConvertToRadians(mRotation.y)) * mDeltaTime * mMoveSpeed;
	mPosition.z -= cosf(XMConvertToRadians(mRotation.y)) * mDeltaTime * mMoveSpeed;
}

void CameraController::MoveUpward()
{
	mPosition.y += mDeltaTime * mMoveSpeed;
}

void CameraController::MoveDownward()
{
	mPosition.y -= mDeltaTime * mMoveSpeed;
}

void CameraController::MoveLeft()
{
	mPosition.x += sinf(XMConvertToRadians(mRotation.y - 90)) * mDeltaTime * mMoveSpeed;
	mPosition.z += cosf(XMConvertToRadians(mRotation.y - 90)) * mDeltaTime * mMoveSpeed;
}

void CameraController::MoveRight()
{
	mPosition.x += sinf(XMConvertToRadians(mRotation.y + 90)) * mDeltaTime * mMoveSpeed;
	mPosition.z += cosf(XMConvertToRadians(mRotation.y + 90)) * mDeltaTime * mMoveSpeed;
}

void CameraController::LookLeft()
{
	mRotation.y -= mDeltaTime * 0.1f;

	if (mRotation.y < 0.0f)
	{
		mRotation.y += 360.0f;
	}
}

void CameraController::LookRight()
{
	mRotation.y += mDeltaTime * 0.1f;

	if (mRotation.y > 360.0f)
	{
		mRotation.y -= 360.0f;
	}
}

void CameraController::LookUpward()
{
	mRotation.x -= mDeltaTime * 0.1f;

	if (mRotation.x > 90.0f)
	{
		mRotation.x = 90.0f;
	}
}

void CameraController::LookDownward()
{
	mRotation.x += mDeltaTime * 0.1f;

	if (mRotation.x < -90.0f)
	{
		mRotation.x = -90.0f;
	}
}

void CameraController::IncreaseMoveSpeed()
{
	mMoveSpeed += 0.01f;
}

void CameraController::DecreaseMoveSpeed()
{
	mMoveSpeed -= 0.01f;
}