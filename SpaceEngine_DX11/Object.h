#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <d3d11.h>
#include <DirectXMath.h>

#include "VertexTypes.h"
#include "Utility.h"

using namespace DirectX;

class Object
{
public:
	Object(ID3D11Device*, XMFLOAT3, XMFLOAT3, XMFLOAT3);
	Object();
	~Object();

	void Shutdown();

	void UpdateTransformationMatrix();

	XMFLOAT3* GetWorldPosition() { return &mWorldPosition; }
	XMFLOAT4X4* GetTransformationMatrix() { return &mTransformation; }

protected:


protected:

	XMFLOAT3 mScale;
	XMFLOAT3 mRotation;
	XMFLOAT3 mTranslation;

	XMFLOAT3 mWorldPosition;

	XMFLOAT4X4 mTransformation;

};

#endif
