#ifndef _PLANET_H_
#define _PLANET_H_

#include "Utility.h"
#include "VertexTypes.h"
#include "QuadTree.h"

using namespace std;
using namespace DirectX;

class Planet : public Object
{
public:
	Planet();
	Planet(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation);
	~Planet();

	bool Initialise(ID3D11Device*, HWND hwnd);

	void Render(ID3D11DeviceContext*, ID3D11Device* device, Frustum*, Camera* camera);

	bool BuildBaseCube(ID3D11Device * device);

	int GetIndexCount();

	bool* GetDebug() { return &isDebug; }

	static int* GetDrawCount() { return QuadTree::GetDrawCount(); }

private:

private:

	Terrain** mTerrain;

	QuadTree** mQuadtree;

	ShaderTerrain* mTerrainShader;
	ShaderColor* mColorShader;

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;

	//BoundingBox* mBoundingBox;

	bool isDebug;

};
#endif