// =========================
// Filename: CCamera.h
// =========================
#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class CCamera {
public:
	CCamera();
	CCamera(const CCamera& other);
	~CCamera();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX& viewMatrix);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_viewMatrix;

};