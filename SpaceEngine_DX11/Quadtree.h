#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include "VertexTypes.h"
#include "Terrain.h"
#include "Frustum.h"
#include "ShaderTerrain.h"
#include "ShaderColor.h"
#include "Utility.h"
#include "BoundingBox.h"
#include "Camera.h"

const int TERRAIN_SIZE = 64;

using namespace DirectX;

class QuadTree : public Object
{
private:

	struct Node
	{
		XMFLOAT3 position;
		float width;
		int triangleCount;
		int level;
		VertexType::LitTexture* vertices;
		XMFLOAT4X4 mTransformationMatrix;
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		Node* nodes[4];
	};

public:
	QuadTree(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation);
	~QuadTree();

	bool Initialise(ID3D11Device* device);
	void Shutdown();
	void Render(Frustum* frustum, ID3D11DeviceContext* deviceContext, ID3D11Device* device, ShaderTerrain* shader, ShaderColor* colorShader, Camera* camera, bool renderDebugBox);

	static int* GetDrawCount() { return &mDrawCount; };

private:
	void CreateTreeNode(ID3D11Device* device, Node* node, XMFLOAT3 position, int level);
	void ReleaseNode(Node*);
	void RenderNode(ID3D11DeviceContext* deviceContext, ID3D11Device* device, Node* node, Frustum* frustum, Camera* camera, ShaderTerrain* shader, ShaderColor* colorShader, bool renderDebugBox);

	void SubDivideNode(Node * node, ID3D11Device * device);

private:
	static int mDrawCount;
	Node* mRootNode;
};

#endif