#ifndef _DIRECT3D_H_
#define _DIRECT3D_H_

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

class Direct3D
{
public:
	Direct3D();
	Direct3D(const Direct3D&);
	~Direct3D();

	void* operator new(size_t);
	void operator delete(void*);

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMFLOAT4X4&);
	void GetWorldMatrix(XMFLOAT4X4&);
	void GetOrthoMatrix(XMFLOAT4X4&);

	void GetVideoCardInfo(char* cardName, int& memory);

	void EnableZBuffer();
	void DisableZBuffer();

	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	bool* GetWireframeValue() { return &isWireframe; }
	bool* GetCullMode() { return &cullingMode; }
	void SetRenderState();

private:
	bool mvsync_enabled;
	bool isWireframe;
	bool cullingMode;
	int mvideoCardMemory;
	char mvideoCardDescription[128];
	IDXGISwapChain* mswapChain;
	ID3D11Device* mdevice;
	ID3D11DeviceContext* mdeviceContext;
	ID3D11RenderTargetView* mrenderTargetView;
	ID3D11Texture2D* mdepthStencilBuffer;
	ID3D11DepthStencilState* mdepthStencilState;
	ID3D11DepthStencilView* mdepthStencilView;
	ID3D11RasterizerState* mrasterState;
	XMFLOAT4X4 mprojectionMatrix;
	XMFLOAT4X4 mworldMatrix;
	XMFLOAT4X4 morthoMatrix;
	ID3D11DepthStencilState* mdepthDisabledStencilState;
	ID3D11BlendState* malphaEnableBlendingState;
	ID3D11BlendState* malphaDisableBlendingState;
};

#endif