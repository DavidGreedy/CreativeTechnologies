#include "Frustum.h"
#include "GLOBALS.h"
Frustum::Frustum()
{
	for (int i = 0; i < 6; i++)
	{
		mplanes[i] = XMFLOAT4(0, 0, 0, 0);
	}
}

Frustum::Frustum(const Frustum& other)
{

}

Frustum::~Frustum()
{

}

void Frustum::ConstructFrustum(float screenDepth)
{
	float zMinimum, r;
	XMFLOAT4X4 matrix;

	// Calculate the minimum Z distance in the frustum.
	zMinimum = -Globals::mProjectionMatrix._43 / Globals::mProjectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	Globals::mProjectionMatrix._33 = r;
	Globals::mProjectionMatrix._43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	XMStoreFloat4x4(&matrix, XMMatrixMultiply(XMLoadFloat4x4(&Globals::mViewMatrix), XMLoadFloat4x4(&Globals::mProjectionMatrix)));

	// Calculate near plane of frustum.
	mplanes[0].x = matrix._14 + matrix._13;
	mplanes[0].y = matrix._24 + matrix._23;
	mplanes[0].z = matrix._34 + matrix._33;
	mplanes[0].w = matrix._44 + matrix._43;
	XMPlaneNormalize(XMLoadFloat4(&mplanes[0]));

	// Calculate far plane of frustum.
	mplanes[1].x = matrix._14 - matrix._13;
	mplanes[1].y = matrix._24 - matrix._23;
	mplanes[1].z = matrix._34 - matrix._33;
	mplanes[1].w = matrix._44 - matrix._43;
	XMPlaneNormalize(XMLoadFloat4(&mplanes[1]));

	// Calculate left plane of frustum.
	mplanes[2].x = matrix._14 + matrix._11;
	mplanes[2].y = matrix._24 + matrix._21;
	mplanes[2].z = matrix._34 + matrix._31;
	mplanes[2].w = matrix._44 + matrix._41;
	XMPlaneNormalize(XMLoadFloat4(&mplanes[2]));

	// Calculate right plane of frustum.
	mplanes[3].x = matrix._14 - matrix._11;
	mplanes[3].y = matrix._24 - matrix._21;
	mplanes[3].z = matrix._34 - matrix._31;
	mplanes[3].w = matrix._44 - matrix._41;
	XMPlaneNormalize(XMLoadFloat4(&mplanes[3]));

	// Calculate top plane of frustum.
	mplanes[4].x = matrix._14 - matrix._12;
	mplanes[4].y = matrix._24 - matrix._22;
	mplanes[4].z = matrix._34 - matrix._32;
	mplanes[4].w = matrix._44 - matrix._42;
	XMPlaneNormalize(XMLoadFloat4(&mplanes[4]));

	// Calculate bottom plane of frustum.
	mplanes[5].x = matrix._14 + matrix._12;
	mplanes[5].y = matrix._24 + matrix._22;
	mplanes[5].z = matrix._34 + matrix._32;
	mplanes[5].w = matrix._44 + matrix._42;
	XMPlaneNormalize(XMLoadFloat4(&mplanes[5]));

	return;
}


bool Frustum::CheckPoint(XMFLOAT3 point)
{
	for (int i = 0; i < 6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4(point.x, point.y, point.z, 1.0f))).m128_f32[0] < 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool Frustum::CheckBox(XMFLOAT3 position, XMFLOAT3 radius)
{
	// Check if any one point of the cube is in the view frustum.
	for (int i = 0; i < 6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x - radius.x), (position.y - radius.y), (position.z - radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x + radius.x), (position.y - radius.y), (position.z - radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x - radius.x), (position.y + radius.y), (position.z - radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x + radius.x), (position.y + radius.y), (position.z - radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x - radius.x), (position.y - radius.y), (position.z + radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x + radius.x), (position.y - radius.y), (position.z + radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x - radius.x), (position.y + radius.y), (position.z + radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&mplanes[i]), XMLoadFloat4(&XMFLOAT4((position.x + radius.x), (position.y + radius.y), (position.z + radius.z), 1.0f))).m128_f32[0] >= 0.0f)
		{
			continue;
		}

		return false;
	}
	return true;
}