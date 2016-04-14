#include "QuadTree.h"
#include "Utility.h"

QuadTree::QuadTree(ID3D11Device* device, XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 translation) : Object(device, scale, rotation, translation)
{
	mRootNode = 0;

	Initialise(device);
}

QuadTree::~QuadTree()
{

}

bool QuadTree::Initialise(ID3D11Device* device)
{
	mRootNode = new Node;
	if (!mRootNode)
	{
		return false;
	}

	CreateTreeNode(device, mRootNode, mTranslation, 1);

	return true;
}

void QuadTree::Shutdown()
{
	// Recursively release the quad tree data.
	if (mRootNode)
	{
		ReleaseNode(mRootNode);
		delete mRootNode;
		mRootNode = 0;
	}

	return;
}

void QuadTree::Render(Frustum* frustum, ID3D11DeviceContext* deviceContext, ID3D11Device* device, ShaderTerrain* shader, ShaderColor* colorShader, Camera* camera, bool renderDebugBox)
{
	// Reset the number of triangles that are drawn for this frame.
	mDrawCount = 0;

	// Render each node that is visible starting at the parent node and moving down the tree.
	RenderNode(deviceContext, device, mRootNode, frustum, camera, shader, colorShader, renderDebugBox);

	return;
}


void QuadTree::CreateTreeNode(ID3D11Device* device, Node* node, XMFLOAT3 position, int level)
{
	int numTriangles, i, count, vertexCount, index, vertexIndex;
	float offsetX, offsetY, offsetZ;
	VertexType::LitTexture* vertices;
	unsigned long* indices;
	bool result;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	node->level = level;

	node->position = position;

	node->width = 100 * ((float)TERRAIN_SIZE / powf(2.0f, level));

	Terrain* tmpTerrain = new Terrain(device, mScale, XMFLOAT3(0, 0, 0), position, TERRAIN_SIZE, node->width * 2, L"Yellow.dds", level);

	XMStoreFloat4x4(&node->mTransformationMatrix, XMMatrixMultiply(XMLoadFloat4x4(&*tmpTerrain->GetTransformationMatrix()), XMLoadFloat4x4(&mTransformation)));

	vertexCount = tmpTerrain->GetVertexCount();
	node->triangleCount = vertexCount / 3;

	node->vertices = new VertexType::LitTexture[vertexCount];
	tmpTerrain->CopyVertices(node->vertices);

	node->vertexBuffer = 0;
	node->indexBuffer = 0;


	node->nodes[0] = 0;
	node->nodes[1] = 0;
	node->nodes[2] = 0;
	node->nodes[3] = 0;

	vertices = new VertexType::LitTexture[vertexCount];
	indices = new unsigned long[vertexCount];

	index = 0;

	// Go through all the triangles in the vertex list.
	for (i = 0; i < node->triangleCount; i++)
	{
		vertexIndex = i * 3;

		for (int i = 0; i < 3; i++)
		{
			// Get the three vertices of this triangle from the vertex list.
			vertices[index].position = node->vertices[vertexIndex].position;
			vertices[index].texture = node->vertices[vertexIndex].texture;
			vertices[index].normal = node->vertices[vertexIndex].normal;
			node->vertices[index] = vertices[index];
			indices[index] = index;
			vertexIndex++;
			index++;
		}
	}

	// Set up the description of the vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType::LitTexture) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &node->vertexBuffer);

	// Set up the description of the index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * vertexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	device->CreateBuffer(&indexBufferDesc, &indexData, &node->indexBuffer);

	delete tmpTerrain;
	tmpTerrain = 0;

	delete[] node->vertices;
	node->vertices = 0;
	// Release the vertex and index arrays now that the data is stored in the buffers in the node.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	if (node->level < 5)
	{
		SubDivideNode(node, device);
	}

	return;
}

void QuadTree::ReleaseNode(Node* node)
{
	int i;

	// Recursively go down the tree and release the bottom nodes first.
	for (i = 0; i < 4; i++)
	{
		if (node->nodes[i] != 0)
		{
			ReleaseNode(node->nodes[i]);
		}
	}

	// Release the vertex buffer for this node.
	if (node->vertexBuffer)
	{
		node->vertexBuffer->Release();
		node->vertexBuffer = 0;
	}

	// Release the index buffer for this node.
	if (node->indexBuffer)
	{
		node->indexBuffer->Release();
		node->indexBuffer = 0;
	}

	if (node->vertices)
	{
		delete[] node->vertices;
		node->vertices = 0;
	}

	// Release the four child nodes.
	for (i = 0; i < 4; i++)
	{
		if (node->nodes[i])
		{
			delete node->nodes[i];
			node->nodes[i] = 0;
		}
	}

	return;
}

void QuadTree::RenderNode(ID3D11DeviceContext* deviceContext, ID3D11Device* device, Node* node, Frustum* frustum, Camera* camera, ShaderTerrain* shader, ShaderColor* colorShader, bool renderDebugBox)
{
	bool result;
	int count, i, indexCount;
	unsigned int stride, offset;

	XMFLOAT4 pos = XMFLOAT4(node->position.x, node->position.y, node->position.z, 1.0);

	XMStoreFloat4(&pos, XMVector4Transform(XMLoadFloat4(&pos), XMLoadFloat4x4(&mTransformation)));

	if (!frustum->CheckBox(XMFLOAT3(pos.x, pos.y, pos.z), XMFLOAT3(node->width, node->width, node->width)))
	{
		//return;
	}

	float changeDist = (50 * (256 / pow(2, node->level)) + 1000);
	float dist = Utility::Float3Distance(camera->GetPosition(), XMFLOAT3(pos.x, pos.y, pos.z));

	if (dist < changeDist)
	{
		count = 0;
		for (i = 0; i < 4; i++)
		{
			if (node->nodes[i] != 0)
			{
				count++;
				RenderNode(deviceContext, device, node->nodes[i], frustum, camera, shader, colorShader, renderDebugBox);
			}
			else if (node->level < 5)
			{
				//SubDivideNode(node, device);
			}
		}
		if (count != 0)
		{
			return;
		}
	}

	shader->SetShaderParameters(deviceContext, Terrain::GetTexture(0), Terrain::GetTexture(1), Terrain::GetTexture(2), mTransformation);

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType::LitTexture);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &node->vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(node->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Determine the number of indices in this node.
	indexCount = node->triangleCount * 3;

	// Call the terrain shader to render the polygons in this node.
	shader->RenderShader(deviceContext, indexCount);

	// Increase the count of the number of polygons that have been rendered during this frame.
	if (node->triangleCount != 0)
	{
		mDrawCount += node->triangleCount;
	}

	if (renderDebugBox)
	{
		//node->mBoundingBox->Render(deviceContext, colorShader);
	}

	return;
}

void QuadTree::SubDivideNode(Node* node, ID3D11Device* device)
{
	XMFLOAT4 pos = XMFLOAT4(node->position.x, node->position.y, node->position.z, 1.0);

	XMStoreFloat4(&pos, XMVector4Transform(XMLoadFloat4(&pos), XMLoadFloat4x4(&node->mTransformationMatrix)));

	XMFLOAT3 positions[4] =
	{
		XMFLOAT3(node->position.x - (node->width / 2), 0 ,node->position.z + (node->width / 2)),
		XMFLOAT3(node->position.x + (node->width / 2), 0 ,node->position.z + (node->width / 2)),
		XMFLOAT3(node->position.x + (node->width / 2), 0 ,node->position.z - (node->width / 2)),
		XMFLOAT3(node->position.x - (node->width / 2), 0 ,node->position.z - (node->width / 2))
	};

	for (int i = 0; i < 4; i++)
	{
		node->nodes[i] = new Node();
		CreateTreeNode(device, node->nodes[i], positions[i], node->level + 1);
	}
}