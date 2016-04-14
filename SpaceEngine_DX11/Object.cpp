#include "Object.h"

Object::Object(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation)
{
	mScale = scale;
	mRotation = rotation;
	mTranslation = translation;

	mTransformation = {};

	UpdateTransformationMatrix();
}

Object::Object()
{
	mScale = XMFLOAT3(1, 1, 1);
	mRotation = XMFLOAT3(0, 0, 0);
	mTranslation = XMFLOAT3(0, 0, 0);

	UpdateTransformationMatrix();
}

Object::~Object()
{
}

void Object::Shutdown()
{
}

void Object::UpdateTransformationMatrix()
{
	XMFLOAT4X4 s, r, t;

	XMStoreFloat4x4(&s, XMMatrixScalingFromVector(XMLoadFloat3(&mScale)));
	XMStoreFloat4x4(&r, XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&mRotation)));
	XMStoreFloat4x4(&t, XMMatrixTranslationFromVector(XMLoadFloat3(&mTranslation)));

	XMStoreFloat4x4(&mTransformation, XMLoadFloat4x4(&(s * r * t)));
}