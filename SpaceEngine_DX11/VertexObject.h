#ifndef _VERTEX_OBJECT_H_
#define _VERTEX_OBJECT_H_

#include "Object.h"
#include "ShaderTerrain.h"
#include "PerlinNoise.h"

class VertexObject : public Object
{
public:
	VertexObject(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation, int vertexGridSize, float gridSize, int level);
	~VertexObject();

	void Render(ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* rockTexture, ID3D11ShaderResourceView* snowTexture, ShaderTerrain * shader);

	int GetVertexCount() { return mVertexCount; }
	void CopyVertices(void* vertices) { memcpy(vertices, mVertices, sizeof(VertexType::LitTexture)* mVertexCount); }

protected:

	void InitialiseVertices();
	void CreateVertexGrid();

	void BuildVertexBuffer(ID3D11Device* device);
	void BuildIndexBuffer(ID3D11Device* device);

	void SpherifyVertices();
	void SpherifyVertex(XMFLOAT3& vertexPosition, float radius);

	void CalculateNormals();

	XMFLOAT3 CalculateSurfaceNormal(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	void CalculateTextureCoordinates();


	void AddNoiseToVertices();

	void AddNoise(XMFLOAT3& vertexPosition, XMFLOAT3 direction);

protected:

	int mVertexGridSize;
	float mGridSize;
	int mVertexCount;
	int mLevel;

	VertexType::LitTexture* mVertexInformation;
	VertexType::LitTexture* mVertices;
	unsigned long* mIndices;

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;

};

#endif
