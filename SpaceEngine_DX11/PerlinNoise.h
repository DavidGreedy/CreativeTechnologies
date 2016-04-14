#ifndef _PERLINNOISE_H
#define _PERLINNOISE_H
#include <DirectXMath.h>

using namespace DirectX;

class PerlinNoise {
public:
	PerlinNoise();

	static float Noise1(float x);
	static float Noise2(float x, float y);
	static float Noise3(float x, float y, float z);
	static float Noise4(float x, float y, float z, float w);

	static float Periodic1D(float x, int px);
	static float Periodic2D(float x, float y, int px, int py);
	static float Periodic3D(float x, float y, float z, int px, int py, int pz);
	static float Periodic4D(float x, float y, float z, float w, int px, int py, int pz, int pw);

	static float FractalPeriodic1D(float x, int px, int octaves, float persistence);
	static float FractalPeriodic2D(float x, float y, int px, int py, int octaves, float persistence);
	static float FractalPeriodic3D(float x, float y, float z, int px, int py, int pz, int octaves, float persistence);
	static float FractalPeriodic3D(XMFLOAT3 position, XMFLOAT3 period, int octaves, float persistence);




private:
	//static float Fade(float);
	//static float Lerp(float, float, float);
	static float Grad1(int, float);
	static float Grad2(int, float, float);
	static float Grad3(int, float, float, float);
	static float Grad4(int, float, float, float, float);

};

#endif