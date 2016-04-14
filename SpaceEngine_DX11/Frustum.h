#ifndef _FRUSTUM_H_
#define _FRUSTUM_H_

#include <DirectXMath.h>
using namespace DirectX;

class Frustum
{
public:
	Frustum();
	Frustum(const Frustum&);
	~Frustum();

	void ConstructFrustum(float);

	bool CheckPoint(XMFLOAT3);
	bool CheckBox(XMFLOAT3, XMFLOAT3);

private:
	XMFLOAT4 mplanes[6];
};

#endif