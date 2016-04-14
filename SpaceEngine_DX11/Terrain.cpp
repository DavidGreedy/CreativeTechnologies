#include "Terrain.h"

Texture* Terrain::mTexture; //Forward declaration of texture object

Terrain::Terrain(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation, int vertexGridSize, float gridSize, WCHAR* textureFileName, int level) : VertexObject(device, scale, rotation, translation, vertexGridSize, gridSize, level)
{
	if (mTexture == NULL)
	{
		mTexture = new Texture[3];
		LoadTexture(device, 0, L"Textures/Red.dds");
		LoadTexture(device, 1, L"Textures/Grey.dds");
		LoadTexture(device, 2, L"Textures/Blue.dds");

		DBOUT("Textures Initialised.");
	}
	GenerateTerrain(device);
}

Terrain::~Terrain()
{

}

ID3D11ShaderResourceView* Terrain::GetTexture(int index)
{
	return mTexture[index].GetTexture();
}

void Terrain::GenerateTerrain(ID3D11Device* device)
{
	VertexObject::CreateVertexGrid();

	VertexObject::SpherifyVertices();

	VertexObject::AddNoiseToVertices();

	VertexObject::CalculateNormals();

	VertexObject::CalculateTextureCoordinates();

	VertexObject::InitialiseVertices();

	//VertexObject::BuildVertexBuffer(device);

	//VertexObject::BuildIndexBuffer(device);
}

bool Terrain::LoadTexture(ID3D11Device* device, int index, WCHAR* filename)
{
	if (!mTexture[index].Initialize(device, filename))
	{
		return false;
	}
	return true;
}