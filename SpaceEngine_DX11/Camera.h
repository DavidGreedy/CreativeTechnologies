#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void* operator new(size_t);
	void  operator delete(void*);

	void SetPosition(XMFLOAT3);
	void SetRotation(XMFLOAT3);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMFLOAT4X4&);

private:
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMFLOAT4X4 mviewMatrix;
};
#endif