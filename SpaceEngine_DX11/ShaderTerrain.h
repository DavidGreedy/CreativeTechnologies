#ifndef _SHADER_TERRAIN_H_
#define _SHADER_TERRAIN_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <D3DCompiler.h>
#include <fstream>
#include <vector>
#include "VertexTypes.h"
#include "GLOBALS.h"

using namespace DirectX;

class ShaderTerrain
{
private:

	struct MatrixBufferType
	{
		XMFLOAT4X4 world;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
		XMFLOAT4X4 transformation;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;
	};

public:
	ShaderTerrain(ID3D11Device* device, HWND hwnd, WCHAR* _Filename);
	~ShaderTerrain();

	bool Initialise(ID3D11Device * device, HWND hwnd, WCHAR * _Filename);

	bool Render(ID3D11DeviceContext * deviceContext, int indexCount, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* rockTexture, ID3D11ShaderResourceView* snowTexture, XMFLOAT4X4 transformationMatrix);

	void RenderShader(ID3D11DeviceContext * deviceContext, int indexCount);

	bool SetShaderParameters(ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* rockTexture, ID3D11ShaderResourceView* snowTexture, XMFLOAT4X4 transformationMatrix);


private:
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

private:
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
	ID3D11InputLayout* mLayout;
	ID3D11SamplerState* mSampleState;
	ID3D11Buffer* mMatrixBuffer;
	ID3D11Buffer* mLightBuffer;

};

#endif