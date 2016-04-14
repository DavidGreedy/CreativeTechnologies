#ifndef _VERTEX_TYPES_H_
#define _VERTEX_TYPES_H_

#include <DirectXMath.h>

using namespace DirectX;

//Different types of vertex depending on application
namespace VertexType
{
	struct Vertex
	{
		XMFLOAT3 position;

		Vertex()
		{
			position = XMFLOAT3(0, 0, 0);
		}

		Vertex(XMFLOAT3 pos)
		{
			position = pos;
		}
	};

	struct Color : public Vertex
	{
		XMFLOAT4 color;

		Color() : Vertex()
		{
			color = XMFLOAT4(1, 1, 1, 1);
		}

		Color(XMFLOAT3 pos, XMFLOAT4 col) : Vertex(pos)
		{
			color = col;
		}
	};

	struct Texture : public Vertex
	{
		XMFLOAT2 texture;
	};

	struct LitColor : public Vertex
	{
		XMFLOAT4 color;
		XMFLOAT3 normal;
	};

	struct LitTexture : public Vertex
	{
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
}

#endif
