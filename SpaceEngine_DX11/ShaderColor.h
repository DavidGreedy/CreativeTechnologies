#ifndef _SHADERCOLOR_H_
#define _SHADERCOLOR_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <D3DCompiler.h>
#include <fstream>

using namespace std;
using namespace DirectX;

class ShaderColor
{
private:

	struct MatrixBufferType
	{
		XMFLOAT4X4 world;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
		XMFLOAT4X4 transformation;
	};

public:
	ShaderColor();
	ShaderColor(const ShaderColor&);
	~ShaderColor();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMFLOAT4X4);
	bool SetShaderParameters(ID3D11DeviceContext*, XMFLOAT4X4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
	ID3D11InputLayout* mLayout;
	ID3D11Buffer* mMatrixBuffer;
};

#endif