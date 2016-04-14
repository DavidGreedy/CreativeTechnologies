#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "VertexObject.h"
#include "Texture.h"

class Terrain : public VertexObject
{
public:
	Terrain(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation, int vertexGridSize, float gridSize, WCHAR* textureFileName, int level);
	~Terrain();

	static ID3D11ShaderResourceView* GetTexture(int index);

protected:

	void GenerateTerrain(ID3D11Device* device);

	bool LoadTexture(ID3D11Device * device, int index, WCHAR * filename);

protected:

	static Texture* mTexture;
};

#endif