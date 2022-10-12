// =========================
// Filename: CTexture.h
// =========================
#pragma once

#include <d3d11.h>
#include <stdio.h>

class CTexture 
{
public:
	CTexture();
	CTexture(const CTexture&);
	~CTexture();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool Load(const char*, int&, int&, int&);

	unsigned char* m_image;
	ID3D11Texture2D* m_texture;
	ID3D11ShaderResourceView* m_textureView;

};