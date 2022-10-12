// =========================
// Filename: CModel.cpp
// =========================

#include "CModel.h"
#include "Common.h"

CModel::CModel() : m_vertexBuffer(nullptr), m_indexBuffer(nullptr), m_texture(nullptr)
{

}

CModel::CModel(const CModel& other)
{

}

CModel::~CModel()
{

}

bool CModel::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* textureFilename)
{
	bool result;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result) 
	{
		return false;
	}

	// Load the texure for this model.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void CModel::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();
	
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void CModel::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int CModel::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* CModel::GetTexture()
{
	return m_texture->GetTexture();
}

bool CModel::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices) 
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertices[0].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertices[1].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[2].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertices[2].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[3].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
	vertices[3].uv = XMFLOAT2(1.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void CModel::ShutdownBuffers()
{
	// Release the index buffer.
	SAFE_RELEASE(m_indexBuffer);

	// Release the vertex buffer.
	SAFE_RELEASE(m_vertexBuffer);

	return;
}

void CModel::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set the vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assmbler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assmbler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex_buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
	return;
}

bool CModel::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename)
{
	bool result;

	// Create and initlize the texture object.
	m_texture = new CTexture;

	result = m_texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void CModel::ReleaseTexture()
{
	// Release the texture object.
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = nullptr;
	}

	return;
}