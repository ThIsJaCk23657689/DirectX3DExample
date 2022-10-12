// =========================
// Filename: CModel.h
// =========================
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "CTexture.h"

using namespace DirectX;

class CModel
{
public:
	CModel();
	CModel(const CModel&);
	~CModel();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	struct VertexType 
	{
		XMFLOAT3 position;
		XMFLOAT2 uv;
	};

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void ReleaseTexture();

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount, m_indexCount;
	CTexture* m_texture;

};