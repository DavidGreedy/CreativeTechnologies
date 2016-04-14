#include "BoundingBox.h"
#include "Utility.h"

BoundingBox::BoundingBox(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation) : VertexObject(device, scale, rotation, translation, 36, 1, 0)
{
	/*mColor = XMFLOAT4(0, 1, 0, 0.1f);

	mVertices = new VertexType::LitTexture[36];

	VertexType::Color vertices[8] =
	{
		VertexType::Color(XMFLOAT3(-0.5f, -0.5f, 0.5f),mColor),
		VertexType::Color(XMFLOAT3(0.5f, -0.5f,0.5f), mColor),
		VertexType::Color(XMFLOAT3(0.5f, 0.5f, 0.5f), mColor),
		VertexType::Color(XMFLOAT3(-0.5f, 0.5f,0.5f), mColor),
		VertexType::Color(XMFLOAT3(-0.5f, -0.5f, -0.5f), mColor),
		VertexType::Color(XMFLOAT3(0.5f, -0.5f, -0.5f), mColor),
		VertexType::Color(XMFLOAT3(0.5f, 0.5f, -0.5f), mColor),
		VertexType::Color(XMFLOAT3(-0.5f, 0.5f, -0.5f), mColor),
	};

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

	int index = 0;

	mVertexCount = 36;

	mVertices = new VertexType::Color[8];
	mIndices = new unsigned long[36];
	for (int i = 0; i < 8; i++)
	{
		mVertices[index++] = vertices[i];
	}

	index = 0;
	for (int i = 0; i < 36; i++)
	{
		mIndices[index++] = indices[i];
	}

	VertexObject::BuildVertexBuffer(device);
	VertexObject::BuildIndexBuffer(device);*/
}

void BoundingBox::InitBuffers(ID3D11Device* device)
{
	VertexType::Color mVertices[8] =
	{
		//VertexType::Color(XMFLOAT3(mPosition.x - mSize.x, mPosition.y - mSize.y, mPosition.z + mSize.z),mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x + mSize.x, mPosition.y - mSize.y, mPosition.z + mSize.z), mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x + mSize.x, mPosition.y + mSize.y, mPosition.z + mSize.z), mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x - mSize.x, mPosition.y + mSize.y, mPosition.z + mSize.z), mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x - mSize.x, mPosition.y - mSize.y, mPosition.z - mSize.z), mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x + mSize.x, mPosition.y - mSize.y, mPosition.z - mSize.z), mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x + mSize.x, mPosition.y + mSize.y, mPosition.z - mSize.z), mColor),
		//VertexType::Color(XMFLOAT3(mPosition.x - mSize.x, mPosition.y + mSize.y, mPosition.z - mSize.z), mColor),

		VertexType::Color(XMFLOAT3(-0.5f, -0.5f, 0.5f),mColor),
		VertexType::Color(XMFLOAT3(0.5f, -0.5f,0.5f), mColor),
		VertexType::Color(XMFLOAT3(0.5f, 0.5f, 0.5f), mColor),
		VertexType::Color(XMFLOAT3(-0.5f, 0.5f,0.5f), mColor),
		VertexType::Color(XMFLOAT3(-0.5f, -0.5f, -0.5f), mColor),
		VertexType::Color(XMFLOAT3(0.5f, -0.5f, -0.5f), mColor),
		VertexType::Color(XMFLOAT3(0.5f, 0.5f, -0.5f), mColor),
		VertexType::Color(XMFLOAT3(-0.5f, 0.5f, -0.5f), mColor),
	};

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

	VertexObject::BuildVertexBuffer(device);
	VertexObject::BuildIndexBuffer(device);

	//// Set up the description of the static vertex buffer.
	//vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//vertexBufferDesc.ByteWidth = sizeof(VertexType::Color) * 8;
	//vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexBufferDesc.CPUAccessFlags = 0;
	//vertexBufferDesc.MiscFlags = 0;
	//vertexBufferDesc.StructureByteStride = 0;

	//vertexData.pSysMem = mVertices;
	//vertexData.SysMemPitch = 0;
	//vertexData.SysMemSlicePitch = 0;

	//device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);

	//indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//indexBufferDesc.ByteWidth = sizeof(unsigned int) * 36;
	//indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//indexBufferDesc.CPUAccessFlags = 0;
	//indexBufferDesc.MiscFlags = 0;
	//indexBufferDesc.StructureByteStride = 0;

	//indexData.pSysMem = (void*)indices;
	//indexData.SysMemPitch = 0;
	//indexData.SysMemSlicePitch = 0;

	//device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);
}
