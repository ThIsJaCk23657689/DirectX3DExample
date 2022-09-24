// =========================
// Filename: CGraphics.cpp
// =========================

#include "CGraphics.h"

CGraphics::CGraphics() : m_D3D(nullptr)
{
}

CGraphics::CGraphics(const CGraphics& other)
{
}

CGraphics::~CGraphics()
{
}

bool CGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    bool result;

    // Create the Direct3D object.
    m_D3D = new CD3D;
    if (!m_D3D)
    {
        return false;
    }

    // Initialize the Direct3D Object
    result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!m_D3D)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
        return false;
    }

    return true;
}

void CGraphics::Shutdown()
{
    if (m_D3D)
    {
        m_D3D->Shutdown();
        delete m_D3D;
        m_D3D = nullptr;
    }

    return;
}

bool CGraphics::Frame()
{
    bool result;

    // Render the graphics scene.
    result = Render();
    if (!result)
    {
        return false;
    }

    return true;
}

bool CGraphics::Render()
{
    // Clear the buffers to begin the scene.
    m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

    // Present the rendered scene to the screen.
    m_D3D->EndScene();

    return true;
}