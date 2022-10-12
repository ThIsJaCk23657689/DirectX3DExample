// =========================
// Filename: CTexture.cpp
// =========================

#include "CTexture.h"
#include "Common.h"
#include "stb_image.h"
#include <vector>

CTexture::CTexture() :
	m_image(nullptr),
	m_texture(nullptr),
	m_textureView(nullptr)
{

}

CTexture::CTexture(const CTexture& other)
{

}

CTexture::~CTexture()
{

}

bool CTexture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename)
{
	bool result;
	int width, height, channel;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	// Load the image
	result = Load(filename, width, height, channel);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the image data into the texture.
	deviceContext->UpdateSubresource(m_texture, 0, NULL, m_image, rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture.
	hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
	if (FAILED(hResult))
	{
		return false;
	}

	// Generate mipmaps for this texture.
	deviceContext->GenerateMips(m_textureView);

	// Release the image data now that image data has been loaded into the texture.
	stbi_image_free(m_image);

	return true;
}

void CTexture::Shutdown()
{
	SAFE_RELEASE(m_textureView);
	SAFE_RELEASE(m_texture);
	return;
}

ID3D11ShaderResourceView* CTexture::GetTexture()
{
	return m_textureView;
}

bool CTexture::Load(const char* filename, int& width, int& height, int& channel)
{
	std::vector<unsigned char> temp;
	m_image = stbi_load(filename, &width, &height, &channel, 4);
	if (m_image)
	{
		return true;
	}
	else
	{
		return false;
	}
}