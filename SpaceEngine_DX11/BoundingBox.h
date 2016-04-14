#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "VertexObject.h"
#include "ShaderColor.h"

class BoundingBox : public VertexObject
{
public:
	BoundingBox(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation);

private:

	void InitBuffers(ID3D11Device*);

public:
	bool renderBox;

private:

	XMFLOAT4 mColor;
};

#endif