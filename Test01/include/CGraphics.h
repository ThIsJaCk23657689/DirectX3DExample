// =========================
// Filename: CGraphics.h
// =========================

#pragma once

#include "CD3D.h"

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
    bool Frame();

private:
    bool Render();
    CD3D* m_D3D;

};