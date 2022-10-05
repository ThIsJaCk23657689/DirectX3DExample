// =========================
// Filename: CGraphics.cpp
// =========================

#include "CGraphics.h"
#include "Common.h"

CGraphics::CGraphics() : 
    m_D3D(nullptr),
    m_Camera(nullptr),
    m_Model(nullptr),
    m_ColorShader(nullptr)
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

    // Initialize the Direct3D Object
    result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
        return false;
    }

    // Create the camera object.
    m_Camera = new CCamera;
    m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

    // Create and initialize the model object.
    m_Model = new CModel;
    result = m_Model->Initialize(m_D3D->GetDevice());
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize model object.", L"Error", MB_OK);
        return false;
    }

    // Create and initialize the color shader object.
    m_ColorShader = new CColorShader;
    result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize color shader object.", L"Error", MB_OK);
        return false;
    }

    return true;
}

void CGraphics::Shutdown()
{
    // Release the color shader object.
    SAFE_SHUTDOWN_AND_DELETE(m_ColorShader);

    // Release the model object.
    SAFE_SHUTDOWN_AND_DELETE(m_Model);

    // Release the camera object.
    SAFE_DELETE(m_Camera);
    
    // Release the D3D object.
    SAFE_SHUTDOWN_AND_DELETE(m_D3D);

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
    XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
    bool result;
    
    // Clear the buffers to begin the scene.
    m_D3D->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

    // Generate the view matrix based on the camera's position.
    m_Camera->Render();

    // Get the world, view and projection matrices from the camera and d3d objects.
    m_D3D->GetWorldMatrix(worldMatrix);
    m_Camera->GetViewMatrix(viewMatrix);
    m_D3D->GetProjectionMatrix(projectionMatrix);

    // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
    m_Model->Render(m_D3D->GetDeviceContext());

    // Render the model using the color shader.
    result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
    if (!result) 
    {
        return false;
    }

    // Present the rendered scene to the screen.
    m_D3D->EndScene();

    return true;
}