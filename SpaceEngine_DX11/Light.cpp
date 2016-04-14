#include "Light.h"

Light::Light()
{

}

Light::Light(const Light& other)
{

}

Light::~Light()
{

}

void Light::SetAmbientColor(float red, float green, float blue, float alpha)
{
	mambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void Light::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	mdiffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void Light::SetDirection(float x, float y, float z)
{
	mdirection = XMFLOAT3(x, y, z);
	return;
}

XMFLOAT4* Light::GetAmbientColor()
{
	return &mambientColor;
}

XMFLOAT4* Light::GetDiffuseColor()
{
	return &mdiffuseColor;
}

XMFLOAT3* Light::GetDirection()
{
	return &mdirection;
}