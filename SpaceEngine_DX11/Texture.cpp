#include "Texture.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

Texture::Texture()
{
	mtexture = 0;
}

Texture::Texture(const Texture& other)
{

}

Texture::~Texture()
{

}

bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	// Load the texture in.
	result = CreateDDSTextureFromFile(device, filename, NULL, &mtexture, NULL, NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	// Release the texture resource.
	if (mtexture)
	{
		mtexture->Release();
		mtexture = 0;
	}

	return;
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return mtexture;
}
