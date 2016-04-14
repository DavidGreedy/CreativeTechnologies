#include "Planet.h"
#include "GLOBALS.h"
#include "Utility.h"

int QuadTree::mDrawCount;

Planet::Planet() : Object()
{
	isDebug = true;
}

Planet::Planet(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation) : Object(device, scale, rotation, translation)
{
	//mBoundingBox = new BoundingBox(device, scale, rotation, translation);
}

Planet::~Planet()
{


}

bool Planet::Initialise(ID3D11Device* device, HWND hwnd)
{

	BuildBaseCube(device);
	mQuadtree = new QuadTree*[6];

	XMFLOAT3 rotations[6] =
	{
		XMFLOAT3(XMConvertToRadians(0),XMConvertToRadians(0),XMConvertToRadians(0)),
		XMFLOAT3(XMConvertToRadians(90),XMConvertToRadians(0),XMConvertToRadians(0)),
		XMFLOAT3(XMConvertToRadians(90),XMConvertToRadians(0),XMConvertToRadians(90)),
		XMFLOAT3(XMConvertToRadians(0),XMConvertToRadians(0),XMConvertToRadians(180)),
		XMFLOAT3(XMConvertToRadians(-90),XMConvertToRadians(0),XMConvertToRadians(0)),
		XMFLOAT3(XMConvertToRadians(-90),XMConvertToRadians(0),XMConvertToRadians(-90)),
	};

	for (int i = 0; i < 6; i++)
	{
		mQuadtree[i] = new QuadTree(device, mScale, rotations[i], mTranslation);
	}

	mTerrainShader = new ShaderTerrain(device, hwnd, L"Shaders/Terrain.fx");

	mColorShader = new ShaderColor();
	mColorShader->Initialize(device, hwnd);

	return false;
}

void Planet::Render(ID3D11DeviceContext* deviceContext, ID3D11Device* device, Frustum* frustum, Camera* camera)
{
	for (int i = 0; i < 6; i++)
	{
		mQuadtree[i]->Render(frustum, deviceContext, device, mTerrainShader, mColorShader, camera, isDebug);
	}

	return;
}

bool Planet::BuildBaseCube(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	XMFLOAT4 mColor = XMFLOAT4(1, 1, 1, 1);

	mTranslation = XMFLOAT3(0, 0, 0);
	mScale = XMFLOAT3(1, 1, 1);

	VertexType::Color mVertices[8] =
	{
		VertexType::Color(XMFLOAT3(-0.5, -0.5, 0.5), mColor),
		VertexType::Color(XMFLOAT3(0.5, -0.5, 0.5), mColor),
		VertexType::Color(XMFLOAT3(0.5, 0.5, 0.5), mColor),
		VertexType::Color(XMFLOAT3(-0.5, 0.5, 0.5), mColor),
		VertexType::Color(XMFLOAT3(-0.5, -0.5, -0.5), mColor),
		VertexType::Color(XMFLOAT3(0.5, -0.5, -0.5), mColor),
		VertexType::Color(XMFLOAT3(0.5, 0.5, -0.5), mColor),
		VertexType::Color(XMFLOAT3(-0.5, 0.5, -0.5), mColor),
	};

	for (size_t i = 0; i < 1; i++)
	{
		mVertices[i].position = mVertices[i].position * mScale;
	}

	unsigned int indices[36] =
	{
		0, 1, 2,
		2, 3, 0,

		1, 5, 6,
		6, 2, 1,

		7, 6, 5,
		5, 4, 7,

		4, 0, 3,
		3, 7, 4,

		4, 5, 1,
		1, 0, 4,

		3, 2, 6,
		6, 7, 3,
	};

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType::Color) * 8;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = mVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * 36;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = (void*)indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);

	return false;
}

int Planet::GetIndexCount()
{
	return 36;
}