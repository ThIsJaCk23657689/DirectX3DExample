// =========================
// Filename: CGraphics.h
// =========================
#pragma once

#include "CD3D.h"
#include "CCamera.h"
#include "CModel.h"
#include "CTextureShader.h"

// =========================
// Globals
// =========================
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class CGraphics
{
public:
    CGraphics();
    CGraphics(const CGraphics&);
    ~CGraphics();

    bool Initialize(int, int, HWND);
    void Shutdown();
    void RenderImGui();
    bool Frame();

private:
    bool Render();

    CD3D* m_D3D;
    CCamera* m_Camera;
    CModel* m_Model;
    CTextureShader* m_TextureShader;

    bool m_ShowDemoWindow;
    XMFLOAT4 m_ClearColor = { 0.45f, 0.55f, 0.60f, 1.0f };

};