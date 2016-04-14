#include "VertexObject.h"

VertexObject::VertexObject(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation, int vertexGridSize, float gridSize, int level) : Object(device, scale, rotation, translation)
{
	mVertexGridSize = vertexGridSize + 1;
	mGridSize = gridSize;
	mVertexCount = 0;
	mLevel = level;

	mVertices = 0;
	mIndices = 0;

	mVertexBuffer = 0;
	mIndexBuffer = 0;
}

VertexObject::~VertexObject()
{
	delete[] mVertices;
	mVertices = 0;

	delete[] mIndices;
	mIndices = 0;
}

void VertexObject::Render(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* rockTexture, ID3D11ShaderResourceView* snowTexture, ShaderTerrain* shader)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType::LitTexture);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case a line list.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Render(deviceContext, mVertexCount, grassTexture, rockTexture, snowTexture, mTransformation);

	return;
}

void VertexObject::InitialiseVertices()
{
	int indices[4];
	int index = 0;

	mVertexCount = (mVertexGridSize - 1) * (mVertexGridSize - 1) * 6;

	mVertices = new VertexType::LitTexture[mVertexCount];
	mIndices = new unsigned long[mVertexCount];

	for (int j = 0; j < mVertexGridSize - 1; j++)
	{
		for (int i = 0; i < mVertexGridSize - 1; i++)
		{
			indices[0] = (mVertexGridSize * j) + i;
			indices[1] = (mVertexGridSize * j) + (i + 1);
			indices[2] = (mVertexGridSize * (j + 1)) + i;
			indices[3] = (mVertexGridSize * (j + 1)) + (i + 1);

			mIndices[index] = index;
			mVertices[index].position = XMFLOAT3(mVertexInformation[indices[2]].position.x, mVertexInformation[indices[2]].position.y, mVertexInformation[indices[2]].position.z);
			mVertices[index].texture = XMFLOAT2(mVertexInformation[indices[2]].texture.x, mVertexInformation[indices[2]].texture.y);
			mVertices[index].normal = XMFLOAT3(mVertexInformation[indices[2]].normal.x, mVertexInformation[indices[2]].normal.y, mVertexInformation[indices[2]].normal.z);
			index++;

			mIndices[index] = index;
			mVertices[index].position = XMFLOAT3(mVertexInformation[indices[3]].position.x, mVertexInformation[indices[3]].position.y, mVertexInformation[indices[3]].position.z);
			mVertices[index].texture = XMFLOAT2(mVertexInformation[indices[3]].texture.x, mVertexInformation[indices[3]].texture.y);
			mVertices[index].normal = XMFLOAT3(mVertexInformation[indices[3]].normal.x, mVertexInformation[indices[3]].normal.y, mVertexInformation[indices[3]].normal.z);
			index++;

			mIndices[index] = index;
			mVertices[index].position = XMFLOAT3(mVertexInformation[indices[0]].position.x, mVertexInformation[indices[0]].position.y, mVertexInformation[indices[0]].position.z);
			mVertices[index].texture = XMFLOAT2(mVertexInformation[indices[0]].texture.x, mVertexInformation[indices[0]].texture.y);
			mVertices[index].normal = XMFLOAT3(mVertexInformation[indices[0]].normal.x, mVertexInformation[indices[0]].normal.y, mVertexInformation[indices[0]].normal.z);
			index++;

			mIndices[index] = index;
			mVertices[index].position = XMFLOAT3(mVertexInformation[indices[0]].position.x, mVertexInformation[indices[0]].position.y, mVertexInformation[indices[0]].position.z);
			mVertices[index].texture = XMFLOAT2(mVertexInformation[indices[0]].texture.x, mVertexInformation[indices[0]].texture.y);
			mVertices[index].normal = XMFLOAT3(mVertexInformation[indices[0]].normal.x, mVertexInformation[indices[0]].normal.y, mVertexInformation[indices[0]].normal.z);
			index++;

			mIndices[index] = index;
			mVertices[index].position = XMFLOAT3(mVertexInformation[indices[3]].position.x, mVertexInformation[indices[3]].position.y, mVertexInformation[indices[3]].position.z);
			mVertices[index].texture = XMFLOAT2(mVertexInformation[indices[3]].texture.x, mVertexInformation[indices[3]].texture.y);
			mVertices[index].normal = XMFLOAT3(mVertexInformation[indices[3]].normal.x, mVertexInformation[indices[3]].normal.y, mVertexInformation[indices[3]].normal.z);
			index++;

			mIndices[index] = index;
			mVertices[index].position = XMFLOAT3(mVertexInformation[indices[1]].position.x, mVertexInformation[indices[1]].position.y, mVertexInformation[indices[1]].position.z);
			mVertices[index].texture = XMFLOAT2(mVertexInformation[indices[1]].texture.x, mVertexInformation[indices[1]].texture.y);
			mVertices[index].normal = XMFLOAT3(mVertexInformation[indices[1]].normal.x, mVertexInformation[indices[1]].normal.y, mVertexInformation[indices[1]].normal.z);
			index++;
		}
	}

	delete[] mVertexInformation;
	mVertexInformation = 0;
}

void VertexObject::CreateVertexGrid()
{
	int index;

	XMFLOAT3 test = mTranslation;

	mVertexInformation = new VertexType::LitTexture[mVertexGridSize * mVertexGridSize];

	float step = (mGridSize) / (mVertexGridSize - 1);

	for (int j = 0; j < mVertexGridSize; j++)
	{
		for (int i = 0; i < mVertexGridSize; i++)
		{
			index = (mVertexGridSize * j) + i;

			mVertexInformation[index].position.x = -((float)mGridSize / 2.0f) + ((float)i * step);
			mVertexInformation[index].position.y = ((float)(((mVertexGridSize - 1) * 100) / 2.0f));
			mVertexInformation[index].position.z = -((float)mGridSize / 2.0f) + ((float)j * step);

			mVertexInformation[index].normal = mVertexInformation[index].position;
		}
	}
}

void VertexObject::BuildVertexBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_BUFFER_DESC vertexBufferDesc;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType::Color) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = mVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);
}

void VertexObject::BuildIndexBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA indexData;
	D3D11_BUFFER_DESC indexBufferDesc;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * mVertexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = (void*)mIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);
}

void VertexObject::SpherifyVertices()
{
	int index;
	for (int j = 0; j < mVertexGridSize; j++)
	{
		for (int i = 0; i < mVertexGridSize; i++)
		{
			index = (mVertexGridSize * j) + i;

			SpherifyVertex(mVertexInformation[index].position, 100);
		}
	}
}

void VertexObject::SpherifyVertex(XMFLOAT3& vertexPosition, float radius)
{
	XMFLOAT4 pos = XMFLOAT4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);

	XMStoreFloat4(&pos, XMVector4Transform(XMLoadFloat4(&pos), XMLoadFloat4x4(&mTransformation)));

	XMFLOAT3 vertexWorldPos = XMFLOAT3(pos.x, pos.y, pos.z);

	XMStoreFloat3(&vertexWorldPos, XMVector3Normalize(XMLoadFloat3(&vertexWorldPos)));

	pos = XMFLOAT4(vertexWorldPos.x, vertexWorldPos.y, vertexWorldPos.z, 1.0);

	//XMStoreFloat4(&pos, XMVector4Transform(XMLoadFloat4(&pos), XMLoadFloat4x4(&Globals::mWorldMatrix)));
	//XMStoreFloat4(&pos, XMVector4Transform(XMLoadFloat4(&pos), XMMatrixInverse(nullptr, XMLoadFloat4x4(&mTransformation))));

	radius = 1000;

	XMStoreFloat3(&vertexPosition, XMLoadFloat3(&(XMFLOAT3(pos.x, pos.y, pos.z) * radius)));
}

void VertexObject::CalculateNormals()
{
	XMFLOAT3 N;

	int a, b, c;

	int count = 0;

	for (int j = 0; j < (mVertexGridSize - 1); j++)
	{
		for (int i = 0; i < (mVertexGridSize - 1); i++)
		{
			a = (j * mVertexGridSize) + i;
			b = (j * mVertexGridSize) + (i + 1);
			c = ((j + 1) * mVertexGridSize) + i;

			N = CalculateSurfaceNormal(mVertexInformation[a].position, mVertexInformation[b].position, mVertexInformation[c].position);

			mVertexInformation[a].normal = N;
			mVertexInformation[b].normal = N;
			mVertexInformation[c].normal = N;

			count += 1;
		}
	}
	count = count;
}

XMFLOAT3 VertexObject::CalculateSurfaceNormal(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
	XMFLOAT3 U, V, N;

	U = b - a;
	V = c - a;

	N.x = (U.y * V.z) - (U.z * V.y);
	N.y = (U.z * V.x) - (U.x * V.z);
	N.z = (U.x * V.y) - (U.y * V.x);

	XMStoreFloat3(&N, XMVector3Normalize(XMLoadFloat3(&N)));

	return N;
}

void VertexObject::CalculateTextureCoordinates()
{
	int incrementCount, i, j, tuCount, tvCount;
	float incrementValue, tuCoordinate, tvCoordinate;

	// Calculate how much to increment the texture coordinates by.
	incrementValue = (float)8 / (float)mVertexGridSize;

	// Calculate how ma.normal.y times to repeat the texture.
	incrementCount = mVertexGridSize / 8;

	// Initialize the tu and tv coordinate values.
	tuCoordinate = 0.0f;
	tvCoordinate = 1.0f;

	// Initialize the tu and tv coordinate indexes.
	tuCount = 0;
	tvCount = 0;

	// Loop through the entire height map and calculate the tu and tv texture coordinates for each vertex.
	for (j = 0; j < mVertexGridSize; j++)
	{
		for (i = 0; i < mVertexGridSize; i++)
		{
			// Store the texture coordinate in the height map.
			mVertexInformation[(mVertexGridSize * j) + i].texture.x = tuCoordinate;
			mVertexInformation[(mVertexGridSize * j) + i].texture.y = tvCoordinate;

			// Increment the tu texture coordinate by the increment value and increment the index by one.
			tuCoordinate += incrementValue;
			tuCount++;

			// Check if at the far right end of the texture and if so then start at the beginning again.
			if (tuCount == incrementCount)
			{
				tuCoordinate = 0.0f;
				tuCount = 0;
			}
		}

		// Increment the tv texture coordinate by the increment value and increment the index by one.
		tvCoordinate -= incrementValue;
		tvCount++;

		// Check if at the top of the texture and if so then start at the bottom again.
		if (tvCount == incrementCount)
		{
			tvCoordinate = 1.0f;
			tvCount = 0;
		}
	}
	return;
}

void VertexObject::AddNoiseToVertices()
{
	int index;
	for (int j = 0; j < mVertexGridSize; j++)
	{
		for (int i = 0; i < mVertexGridSize; i++)
		{
			index = (mVertexGridSize * j) + i;

			XMFLOAT3 direction;

			XMFLOAT4 pos = XMFLOAT4(mVertexInformation[index].position.x, mVertexInformation[index].position.y, mVertexInformation[index].position.z, 1.0);

			XMFLOAT3 vertexWorldPos = XMFLOAT3(pos.x, pos.y, pos.z);

			XMStoreFloat3(&direction, XMVector3Normalize(XMLoadFloat3(&vertexWorldPos)));

			AddNoise(mVertexInformation[index].position, direction);
		}
	}
}

void VertexObject::AddNoise(XMFLOAT3& vertexPosition, XMFLOAT3 direction)
{
	XMFLOAT3 period = XMFLOAT3((mVertexGridSize - 1), (mVertexGridSize - 1), (mVertexGridSize - 1));

	float noiseValue = PerlinNoise::FractalPeriodic3D(vertexPosition, period, 2 + mLevel, 0.5f) * 100;

	XMStoreFloat3(&vertexPosition, XMVectorAdd(XMLoadFloat3(&vertexPosition), XMLoadFloat3(&(direction * noiseValue))));
}
