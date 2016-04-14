#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <DirectXMath.h>
#include <D3D11.h>
#include <Windows.h>
#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

using namespace DirectX;
using namespace std;

inline XMFLOAT3 operator* (XMFLOAT3 &a, XMFLOAT3 &b)
{
	return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline XMFLOAT3 operator* (XMFLOAT3 &a, int &b)
{
	return XMFLOAT3(a.x * b, a.y * b, a.z * b);
}

inline XMFLOAT3 operator+ (XMFLOAT3 &a, XMFLOAT3 &b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline XMFLOAT3 operator- (XMFLOAT3 &a, XMFLOAT3 &b)
{
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline XMFLOAT3 operator* (XMFLOAT3 &a, float &b)
{
	return XMFLOAT3(a.x * b, a.y * b, a.z * b);
}

inline XMFLOAT3 operator/ (XMFLOAT3 &a, int &b)
{
	return XMFLOAT3(a.x / b, a.y / b, a.z / b);
}

inline XMFLOAT3 operator/ (XMFLOAT3 &a, float &b)
{
	return XMFLOAT3(a.x / b, a.y / b, a.z / b);
}

inline XMFLOAT4X4 operator* (const XMFLOAT4X4& M1, const XMFLOAT4X4& M2)
{
	using namespace DirectX;
	XMMATRIX m1 = XMLoadFloat4x4(&M1);
	XMMATRIX m2 = XMLoadFloat4x4(&M2);
	XMMATRIX X = XMMatrixMultiply(m1, m2);

	XMFLOAT4X4 R;
	XMStoreFloat4x4(&R, X);
	return R;
}

inline XMMATRIX operator* (const XMMATRIX& M1, const XMMATRIX& M2)
{
	return XMMatrixMultiply(M1, M2);
}

class Utility
{
public:

	static float Float3Distance(XMFLOAT3 A, XMFLOAT3 B)
	{
		return sqrtf(powf(A.x - B.x, 2.0f) + powf(A.y - B.y, 2.0f) + powf(A.z - B.z, 2.0f));
	}
};


#endif